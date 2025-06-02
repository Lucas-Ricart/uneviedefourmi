#include "AntColony.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>

AntColony::~AntColony() {
    // Clean up dynamically allocated rooms and ants
    for (auto& [name, room] : rooms) delete room;
    for (Ant* ant : ants) delete ant;
}

void AntColony::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int antCount = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Parse number of ants
        if (line.find("f=") == 0) {
            antCount = std::stoi(line.substr(2));
            std::cout << "Number of ants : " << antCount << std::endl;
            rooms["Sv"] = new Room("Sv", antCount);
            rooms["Sd"] = new Room("Sd", antCount);
            // Create ants starting in the "Sv" room
            for (int i = 1; i <= antCount; ++i) {
                ants.push_back(new Ant(i, "Sv"));
                rooms["Sv"]->addAnt(ants.back());
            }
        }
        // Parse connections between rooms
        else if (line.find("-") != std::string::npos) {
            std::istringstream iss(line);
            std::string from, dash, to;
            iss >> from >> dash >> to;
            if (rooms.count(from) && rooms.count(to)) {
                rooms[from]->addAdjacentRoom(rooms[to]);
                rooms[to]->addAdjacentRoom(rooms[from]); // Undirected graph
                std::cout << "Connection between : " << from << " and " << to << " added" << std::endl;
            } else {
                std::cerr << "Error: Unknown room in connection: " << line << std::endl;
            }
        }
        // Parse rooms with specified capacity
        else if (line.find("S") == 0 && line.find("{") != std::string::npos) {
            size_t start = line.find("{") + 1;
            size_t end = line.find("}");
            int capacity = std::stoi(line.substr(start, end - start));
            std::string roomName = line.substr(0, line.find(" "));
            rooms[roomName] = new Room(roomName, capacity);
            std::cout << "Room added : " << roomName << " with capacity " << capacity << std::endl;
        }
        // Parse rooms with default capacity = 1
        else if (line.find("S") == 0) {
            std::string roomName = line;
            roomName.erase(std::remove(roomName.begin(), roomName.end(), ' '), roomName.end());
            if (rooms.find(roomName) == rooms.end()) {
                rooms[roomName] = new Room(roomName, 1); // default capacity
                std::cout << "Room added : " << roomName << " (default capacity)" << std::endl;
            }
        }
    }
}

// Compute shortest distance from all rooms to the exit room using BFS
void AntColony::computeDistancesToExit(const std::string& exitName) {
    distanceToExit.clear();
    // Initialize all distances to -1 (unvisited)
    for (const auto& [name, room] : rooms) {
        distanceToExit[name] = -1;
    }

    if (rooms.find(exitName) == rooms.end()) {
        std::cerr << "Error: Exit room '" << exitName << "' not found.\n";
        return;
    }

    std::queue<Room*> q;
    distanceToExit[exitName] = 0;
    q.push(rooms.at(exitName));

    // BFS traversal to assign distances
    while (!q.empty()) {
        Room* current = q.front();
        q.pop();
        int currentDist = distanceToExit[current->name];

        for (Room* adj : current->adjacentRooms) {
            if (distanceToExit[adj->name] == -1) {
                distanceToExit[adj->name] = currentDist + 1;
                q.push(adj);
            }
        }
    }
}

// Run the ant movement simulation step-by-step
void AntColony::simulate() {
    computeDistancesToExit("Sd");  // Compute distances to exit once before simulation

    // Loop until all ants have reached the exit room "Sd"
    while (rooms["Sd"]->currentAnts.size() < ants.size()) {
        std::cout << "+ + + E" << step++ << " + + +" << std::endl;
        std::vector<std::string> moves;
        bool anyMove = false;

        for (Ant* ant : ants) {
            Room* current = rooms[ant->currentRoom];

            // Ants already at exit do not move
            if (current->name == "Sd") continue;

            // Find adjacent room with the smallest distance to exit and space available
            Room* bestNext = nullptr;
            int bestDist = 1e9;

            for (Room* next : current->adjacentRooms) {
                if (next->canAcceptAnt() &&
                    distanceToExit[next->name] != -1 &&
                    distanceToExit[next->name] < bestDist) {
                    bestDist = distanceToExit[next->name];
                    bestNext = next;
                }
            }

            // Move ant to best room if possible
            if (bestNext) {
                current->removeAnt(ant);
                bestNext->addAnt(ant);
                moves.push_back("f" + std::to_string(ant->id) + " - " + current->name + " - " + bestNext->name);
                anyMove = true;
            }
        }

        // Output all moves this step
        for (const std::string& move : moves) {
            std::cout << move << "\n";
        }

        // If no ants moved this step, simulation is stuck - break loop
        if (!anyMove) {
            std::cout << "No ants could move this step, simulation stuck!\n";
            break;
        }
    }
}

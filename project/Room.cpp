#include "Room.hpp"
#include <algorithm>

Room::Room(const std::string& name, int capacity) : name(name), capacity(capacity) {}

void Room::addAdjacentRoom(Room* room) {
    adjacentRooms.push_back(room);
}

bool Room::canAcceptAnt() const {
    return currentAnts.size() < static_cast<size_t>(capacity);
}

void Room::addAnt(Ant* ant) {
    if (canAcceptAnt()) {
        currentAnts.push_back(ant);
        ant->currentRoom = name;
    }
}

void Room::removeAnt(Ant* ant) {
    currentAnts.erase(std::remove(currentAnts.begin(), currentAnts.end(), ant), currentAnts.end());
}
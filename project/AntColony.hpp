#ifndef ANTCOLONY_HPP
#define ANTCOLONY_HPP

#include <map>
#include <vector>
#include <string>
#include "Ant.hpp"
#include "Room.hpp"

class AntColony {
public:
    std::map<std::string, Room*> rooms;  // Map of room name to room object
    std::vector<Ant*> ants;              // List of all ants
    int step = 1;                        // Current simulation step

    ~AntColony();
    void loadFromFile(const std::string& filename);  // Parse file and initialize colony
    void simulate();                                  // Run simulation

private:
    std::map<std::string, int> distanceToExit; // distances to Sd
    void computeDistancesToExit(const std::string& exitName = "Sd");
};

#endif // ANTCOLONY_HPP
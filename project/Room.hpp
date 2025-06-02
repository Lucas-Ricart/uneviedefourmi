#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include "Ant.hpp"

class Room {
public:
    std::string name;                    // Room name
    int capacity;                        // Max number of ants allowed
    std::vector<Room*> adjacentRooms;   // Adjacent rooms connected to this one
    std::vector<Ant*> currentAnts;      // Ants currently in the room

    Room(const std::string& name, int capacity);
    void addAdjacentRoom(Room* room);   // Add a bidirectional connection
    bool canAcceptAnt() const;          // Check if room has space for one more ant
    void addAnt(Ant* ant);              // Add ant to this room
    void removeAnt(Ant* ant);           // Remove ant from this room
};

#endif // ROOM_HPP
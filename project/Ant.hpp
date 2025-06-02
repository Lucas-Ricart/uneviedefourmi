#ifndef ANT_HPP
#define ANT_HPP

#include <string>

class Ant {
public:
    int id;                      // Unique identifier for each ant
    std::string currentRoom;     // Current room where the ant is located

    Ant(int id, const std::string& startRoom);
};

#endif // ANT_HPP
cmake_minimum_required(VERSION 3.15)
project(AntColonySim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Liste de tous les fichiers source .cpp
set(SOURCES
    main.cpp
    Ant.cpp
    Room.cpp
    AntColony.cpp
)

add_executable(AntColonySim ${SOURCES})

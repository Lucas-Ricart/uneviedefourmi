#include "AntColony.hpp"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    const std::string filename = "../fourmiliere_simple.txt";
    //const std::string filename = "../fourmiliere_zero.txt";
    //const std::string filename = "../fourmiliere_un.txt";
    //const std::string filename = "../fourmiliere_deux.txt";
    //const std::string filename = "../fourmiliere_trois.txt";
    //const std::string filename = "../fourmiliere_quatre.txt";
    //const std::string filename = "../fourmiliere_cinq.txt";
    //const std::string filename = "../everything_everywhere.txt";
    //const std::string filename = "../fourmiliere_3D.txt";
    //const std::string filename = "../salle_d_at-ant.txt";
    AntColony colony;
    colony.loadFromFile(filename);
    colony.simulate();

    return 0;
}
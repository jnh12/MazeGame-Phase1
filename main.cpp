#include <iostream>
#include "Maze.hpp"

int main() {
    Maze genMaze(30,50);

    genMaze.generateMaze();
    genMaze.displayMaze();


    return 0;
}

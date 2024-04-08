#include <iostream>
#include "Maze.hpp"

int main() {
    Maze genMaze(50, 50);

    genMaze.generateMaze();
    genMaze.displayMaze();

    std::cout << "\n\n\n";

    genMaze.navigateMaze();
    genMaze.displayMaze();

    return 0;
}
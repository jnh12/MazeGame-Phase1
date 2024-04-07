#include <iostream>
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "MazeNavigator.hpp"

int main() {
    MazeNavigator genMaze (30,50);


    genMaze.generateMaze();
    genMaze.displayMaze();

    
    genMaze.navigateMaze();
    return 0;
}

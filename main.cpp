#include <iostream>
#include "maze1.hpp"

int main() {
    maze genMaze(30, 50);

    genMaze.generateMaze();
    genMaze.displayMaze();

    return 0;
}

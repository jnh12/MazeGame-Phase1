#include <iostream>
#include "maze-sfml.hpp"

using std::cout;
using std::cin;

int main() {

    int r, c, s; // Temp variables for rows cols and speed

    cout << "Enter Width [Min 10 - Default 50]: ";
    cin >> c;

    cout << "Enter Height [Min 10 - Default 50]: ";
    cin >> r;

    cout << "Enter Speed [Fastest 1 - Slowest 10 - Default 5]: ";
    cin >> s;

    cout << std::endl << "Press ENTER to solve the maze" << std::endl;
    cout << std::endl << "Press BACKSPACE to generate a new maze" << std::endl;
    cout << "Press ESC to close" << std::endl;


    Visualizer v(r, c, s);

    return 0;
}


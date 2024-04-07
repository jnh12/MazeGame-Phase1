#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <algorithm>
#include <queue>

using std::vector;
using std::pair;
using std::priority_queue;
using std::abs;

class Maze {
public:

    int rows;
    int cols;

    int BLOCKED = 0;
    int PASSAGE = 1;
    int SHORTESTPATH = 8; //used for navigation


    vector<vector<int>> arr; // used instead of 2d array since it is easier and is dynamic
    vector<pair<int,int>> frontierList;
    pair<int, int> starting {0,0};
    pair<int, int> ending {rows-1,cols-1}; //initialize start and end cells of the maze before our random search for the start cell

    
    Maze() {
        rows = 0;
        cols = 0;
        arr.assign(rows, vector<int>(cols, BLOCKED)); //fills array with blocked
    }

    Maze(int r, int c) {
        rows = r;
        cols = c;
        arr.assign(rows, vector<int>(cols, BLOCKED)); //fills array with blocked
    }
};
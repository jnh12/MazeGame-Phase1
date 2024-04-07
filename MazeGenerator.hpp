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

class MazeGenerator {
public:

    int rows;
    int cols;

    int BLOCKED = 0;
    int PASSAGE = 1;
    int SHORTESTPATH = 100; //used for navigation


    vector<vector<int>> arr; // used instead of 2d array since it is easier and is dynamic
    vector<pair<int,int>> frontierList;
    pair<int, int> starting {0,0};
    pair<int, int> ending {rows-1,cols-1}; //initialize start and end cells of the maze before our random search for the start cell

    MazeGenerator(int r, int c) {
        rows = r;
        cols = c;
        arr.assign(rows, vector<int>(cols, BLOCKED)); //fills array with blocked
    }

    pair<int, int> pickRandomCell() { // locates random cell in array (if u want to use pair output use .first/.second)
        srand(time(0));
        int randomRow = rand() % rows;
        int randomCol = rand() % cols;

        starting = {randomRow, randomCol};
        return {randomRow, randomCol};
    }

    vector<pair<int, int>>computeFrontierCells(pair<int, int> cell) {
        pair<int, int> top = {cell.first  - 2, cell.second};
        pair<int, int> right = {cell.first, cell.second + 2};
        pair<int, int> bottom = {cell.first + 2, cell.second};
        pair<int, int> left = { cell.first, cell.second - 2};

        vector<pair<int,int>> frontiers; // list of frontiers found

        int cnt = 0; // to avoid dpulicate frontier cells

        // CONDITIONS TO CHECK FOR If THE FRONTIERS EXIST WITHIN BOUNDS OF ARR, AND TO CHECK THAT FRONTIER IS NOT PASSAGE
        if (top.first >= 0 && arr[top.first][top.second] == BLOCKED) {
            cnt = count(frontierList.begin(), frontierList.end(), top);
            if (!cnt) frontiers.push_back(top);
        }

        if (right.second < cols && arr[right.first][right.second] == BLOCKED){
            cnt = count(frontierList.begin(), frontierList.end(), right);
            if (!cnt) frontiers.push_back(right);
        }

        if (bottom.first < rows && arr[bottom.first][bottom.second] == BLOCKED){
            cnt = count(frontierList.begin(), frontierList.end(), bottom);
            if (!cnt) frontiers.push_back(bottom);
        }

        if (left.second >= 0 && arr[left.first][left.second] == BLOCKED){
            cnt = count(frontierList.begin(), frontierList.end(), left);
            if (!cnt) frontiers.push_back(left);
        }

        return frontiers;
    } // finding all possible frontier cells of cell inputted as pair and then return an array that contains frontier cells

    vector<pair<int,int>> getNeighbours(pair<int,int> current) {
        vector<pair<int, int>> neighbors;

        if (current.first - 2 >= 0 && arr[current.first - 2][current.second] == PASSAGE)
            neighbors.push_back({current.first - 2, current.second});

        if (current.second + 2 < cols && arr[current.first][current.second + 2] == PASSAGE)
            neighbors.push_back({current.first, current.second + 2});

        if (current.first + 2 < rows && arr[current.first + 2][current.second] == PASSAGE)
            neighbors.push_back({current.first + 2, current.second});

        if (current.second - 2 >= 0 && arr[current.first][current.second - 2] == PASSAGE)
            neighbors.push_back({current.first, current.second - 2});

        return neighbors;
    }

    vector<vector<int>> generateMaze() {
        srand(time(0));
        int randomRow = rand() % rows;
        int randomCol = rand() % cols;

        starting = {randomRow, randomCol};
        arr[starting.first][starting.second] = PASSAGE;

        frontierList = computeFrontierCells(starting);

        while(!frontierList.empty()){
            int frontierPick = rand() % frontierList.size();
            pair<int, int> current = frontierList[frontierPick];
            frontierList.erase(frontierList.begin() + frontierPick);

            arr[current.first][current.second] = PASSAGE;//

            vector<pair<int,int>> neighbourCells = getNeighbours(current);

            if (!neighbourCells.empty()) {
                int randomPickNeighbour = rand() % neighbourCells.size();
                pair<int, int> randomNeighbor = neighbourCells[randomPickNeighbour]; // pick random neighbour
                pair<int, int> nearNeighbor = {(current.first + randomNeighbor.first) / 2, (current.second + randomNeighbor.second) / 2}; // i just averaged the value of neighbor and current to find middle cell

                arr[nearNeighbor.first][nearNeighbor.second] = PASSAGE;
                arr[randomNeighbor.first][randomNeighbor.second] = PASSAGE;

                vector<pair<int, int>> newFrontierList = computeFrontierCells(current);

                // add the new frontier values to the old list
                for (const auto& frontierCell : newFrontierList) {
                    frontierList.push_back(frontierCell);
                }
            }

            ending = current; //when while terminates, we are left with the last cell of the maze
            return arr;
        }

        std::cout << rows << "x" << cols << " Maze Generated \n\n";
    }

    void displayMaze() {
        std::cout << "Start (XX):\t" << starting.first << " - " << starting.second << "\n";
        std::cout << "Finish (OO):\t" << ending.first << " - " << ending.second << "\n\n";

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (starting.first == i && starting.second == j) { // Start cell
                    std::cout << "XX";
                }
                else if (ending.first == i && ending.second == j) { // Finish cell
                    std::cout << "OO";
                }


                else {
                    if (arr[i][j] == BLOCKED) {
                        std::cout << "##";
                    } else if (arr[i][j] == SHORTESTPATH){    //used for navigating shortest path
                    std::cout << "--";
                    } else {
                        std::cout << "  ";
                    }
                }
            }

            std::cout << "\n";
        }

        std::cout << "\n\n";
    } // just for loop the original 2d array

};
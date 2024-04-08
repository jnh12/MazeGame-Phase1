#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <queue>

using std::vector;
using std::pair;
using std::count;
using std::priority_queue;
using std::abs;

class Maze {
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

    class Cell {   //nested class needed for navigating maze
    public:
        Cell* parent;
        int cost;
        pair<int, int> position;

        Cell(int x, int y): position({x,y}){}   //not sure if we need more contructing statements. we'll see as we write the code
    };


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

    vector<pair<int,int>> getNavNeighbours(pair<int,int> current) {
        vector<pair<int, int>> neighbors;

        if (current.first - 1 >= 0 && arr[current.first - 1][current.second] == PASSAGE)
            neighbors.push_back({current.first - 1, current.second});

        if (current.second + 1 < cols && arr[current.first][current.second + 1] == PASSAGE)
            neighbors.push_back({current.first, current.second + 1});

        if (current.first + 1 < rows && arr[current.first + 1][current.second] == PASSAGE)
            neighbors.push_back({current.first + 1, current.second});

        if (current.second - 1 >= 0 && arr[current.first][current.second - 1] == PASSAGE)
            neighbors.push_back({current.first, current.second - 1});

        return neighbors;
    }


    void generateMaze() {
        srand(time(0));
        int randomRow = (2 * rand()) % rows;
        int randomCol = (2 * rand()) % cols;

        starting = {randomRow, randomCol};
        arr[starting.first][starting.second] = PASSAGE;

        frontierList = computeFrontierCells(starting);

        while(!frontierList.empty()){
            int frontierPick = rand() % frontierList.size();
            pair<int, int> current = frontierList[frontierPick];
            frontierList.erase(frontierList.begin() + frontierPick);

            arr[current.first][current.second] = PASSAGE;

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
        }

        std::cout << rows << "x" << cols << " Maze Generated \n\n";
    }

    void displayMaze() {
        std::cout << "Start (XX):\t" << starting.first << " - " << starting.second << "\n";
        std::cout << "Finish (OO):\t" << ending.first << " - " << ending.second << "\n\n";

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (starting.first == i && starting.second == j) { // Start cell
                    std::cout << " X ";
                }
                else if (ending.first == i && ending.second == j) { // Finish cell
                    std::cout << " 0 ";
                }
                else {
                    if (arr[i][j] == BLOCKED) {
                        std::cout << "###";
                    }
                    else if (arr[i][j] == SHORTESTPATH) {
                        std::cout << " . ";
                    }
                    else {
                        std::cout << "   ";
                    }
                }
            }

            std::cout << "\n";
        }

        std::cout << "\n\n";
    } // just for loop the original 2d array

    vector<vector<int>> costMatrix;

    int heuristic(pair<int, int> a, pair<int, int> b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
        // we use manhattan distance before start and end node (since we can't move diagonally)
    }

    int calculateCost (pair<int, int> cell, pair<int, int> goal) {
        return costMatrix[cell.first][cell.second] + heuristic(cell, goal);
    };


    void navigateMaze() {

        costMatrix.assign(rows, vector<int>(cols, INT_MAX)); // initialize the cost of each cell with infinity

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<pair<int, int>>> parentMatrix(rows, vector<pair<int, int>>(cols, {-1, -1})); // Parent matrix for each cell
        vector<pair<int,int>> path; // array containing positions of each node on the shortest path from start to end goal

        auto compareCells = [&](pair<int, int> a, pair<int, int> b) {
            return calculateCost(a, ending) > calculateCost(b, ending);
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compareCells)> toVISIT(compareCells);


        costMatrix[starting.first][starting.second] = 0;
        toVISIT.push(starting); // add starting cell to the priority queue

        while (!toVISIT.empty()) {
            pair<int, int> currentCell = toVISIT.top();
            toVISIT.pop();

            if (currentCell == ending) {
                std::cout << "Found the end cell!" << std::endl;

                // start building the path backwards
                pair<int, int> temp = currentCell;

                while (temp != starting) {
                    path.push_back(temp);
                    temp = parentMatrix[temp.first][temp.second];
                }

                // push back the starting cell at the end and reverse the vector
                path.push_back(starting);
                reverse(path.begin(), path.end());

                break;
            }

            visited[currentCell.first][currentCell.second] = true;
            vector<pair<int, int>> neighbors = getNavNeighbours(currentCell);

            for (const auto& neighborPos : neighbors) {
                if (!visited[neighborPos.first][neighborPos.second]) {
                    int newCost = costMatrix[currentCell.first][currentCell.second] + 1; // Assuming each move has cost 1

                    if (newCost < costMatrix[neighborPos.first][neighborPos.second]) {  // ADD && toVISIT does not already contain a node with the same position coordinates
                        costMatrix[neighborPos.first][neighborPos.second] = newCost;
                        parentMatrix[neighborPos.first][neighborPos.second] = currentCell;
                        toVISIT.push(neighborPos);
                    }
                }
            }
        }

        for (const auto& p : path) {
            arr[p.first][p.second] = SHORTESTPATH;
        }

    }

};
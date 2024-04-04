#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::vector;
using std::pair;
using std::count;

class maze {
public:

    int rows;
    int cols;

    int BLOCKED = 0;
    int PASSAGE = 1;

    class Cell {   //nested class needed for navigating maze
    public:
        Cell* parent;
        int cost;
        pair<int, int> position;

        Cell(int x, int y): position({x,y}){}   //not sure if we need more contructing statements. we'll see as we write the code
    };

    vector<vector<int>> arr; // used instead of 2d array since it is easier and is dynamic
    vector<pair<int,int>> frontierList;
    pair<int, int> starting {0,0};
    pair<int, int> ending {rows-1,cols-1}; //initialize start and end cells of the maze before our random search for the start cell

    maze(int r, int c) {
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

    void generateMaze() {
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
                    } else {
                        std::cout << "  ";
                    }
                }
            }

            std::cout << "\n";
        }

        std::cout << "\n\n";
    } // just for loop the original 2d array





    void navigateMaze() {

        /* we use manhattan distance before start and end node (since we can't move diagonally)
        d = abs(x1 - x0) + abs(y1 - y0)

        1) we build cost map:
            cost F = distance from starting node + distance from end node
                   = G                           +  H (heuristic)
                   
            moving from each cell forward, backward, to left or right costs 10 each. 

        2) node list of path to the goal cell. we add nodes (of class Cell) to the 
        list one by one as we discover which is the lowest cost from each previous node.
        we start by the starting cell which we initiate as our starting Cell with its respective positions

        3) we create 2 other lists of nodes as arrays of Cells:
         - TOvisit[] aka neighbors list //priority queue. first Cell in first Cell out to process. out first cell to be added to this queued is our starting Cell
         - visited[] //all the Cells we have visited and are done with

        4) when we push the Cells from Tovisit[]:
           -check if cost of the next node to be pushed(visited) is lower than our current node.
            if yes, make it the current node

           -add this node to the visited[] list and remove it from TOvisit

           -check if our current Cell is the ending Cell (compare position pairs of each)
            if yes, done

            *remember to add nodes to TOvisit list only if its position is not alr in the list OR cost is lower than previously added node for same position
            (since we might visit same node twice as part of 2 different paths. must find which is shorter)

    
        */
    }
};
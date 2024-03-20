#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>

using std::vector;
using std::pair;

class MazeGenerator {
public:
    int rows;
    int cols;

    int BLOCKED = 0;
    int PASSAGE = 1;

    vector<vector<int>> arr; // used instead of 2d array since it is easier and is dynamic

    MazeGenerator(int r, int c){
        rows = r;
        cols = c;
        arr.assign(rows, vector<int>(cols, BLOCKED)); //fills array with blocked
    }

    pair<int, int> pickRandomCell() { // locates random cell in array (if u want to use pair output use .first/.second)
        srand(time(0));
        int randomRow = rand() % rows;
        int randomCol = rand() % cols;
        return {randomRow, randomCol};
    }

    vector<pair<int, int>>computeFrontierCells(pair<int, int> cell) {
        pair<int, int> top = {cell.first  - 2, cell.second};
        pair<int, int> right = {cell.first, cell.second +2};
        pair<int, int> bottom ={cell.first + 2, cell.second};
        pair<int, int> left= { cell.first, cell.second-2};

        vector<pair<int,int>> frontiers; //list of forntiers found


        //CONDTIONS TO CHECK FOR If TGHE FRONTIERS EXIST WITHIN BOUNDS OF ARR, AND TO CHECK THAT FRONTIER IS NOT PASSAGE
        if (top.first >= 0 && arr[top.first][top.second] == BLOCKED) {
            frontiers.push_back(top);
        }

        if (right.second < cols && arr[right.first][right.second] == BLOCKED){
            frontiers.push_back(right);
        }

        if (bottom.first < rows && arr[bottom.first][bottom.second] == BLOCKED){
            frontiers.push_back(bottom);
        }

        if (left.second >= 0 && arr[left.first][left.second] == BLOCKED){
            frontiers.push_back(left);
        }

        return frontiers;
    } // implement finding of frontier cells. Cell inputted as pair and then return an array that contains frontier cells

    vector<pair<int,int>> getNeighbours(pair<int,int> current){
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

        pair<int,int> randomPick = pickRandomCell();
        arr[randomPick.first][randomPick.second] = PASSAGE;

        vector<pair<int,int>> frontierList= computeFrontierCells(randomPick);

        while(!frontierList.empty()){
            int frontierPick = rand() % frontierList.size();
            pair<int, int> current = frontierList[frontierPick];
            frontierList.erase(frontierList.begin() + frontierPick);

            vector<pair<int,int>> neighbourCells = getNeighbours(current);


            if (!neighbourCells.empty()) {
                int randomPickNeighbour = rand() % neighbourCells.size();
                pair<int, int> randomNeighbor = neighbourCells[randomPickNeighbour]; //pick ranadom neighbour

                arr[(current.first + randomNeighbor.first) / 2][(current.second + randomNeighbor.second) / 2] = PASSAGE;  // i just averagedthe value of neighbor and current to find middle cell

                arr[randomNeighbor.first][randomNeighbor.second] = PASSAGE;

                vector<pair<int, int>> newfrontierList = computeFrontierCells(randomNeighbor);

                for (const auto& frontierCell : newfrontierList) {
                    frontierList.push_back(frontierCell);
                } // add the new frontier values to the old list
            }


        }
        




        /*
         * 
         * pick random cell as starting point
         * make starting point passage
         * generate frontier cells for starting point and add to list of frontier cells
         *
         * WHILE LIST OF FRONTIER IS NOT EMPTY{
         *  -pick random value from list and set the value between frontier and random value from list to PASSAGE
         *  -find frontier cells of random value from list and add them to list of frontier values
         *  -remove frontier cell from frontier list.
         *  }
         *
         * optional: make last frontier cell as the end point
        */

    }

    void displayMaze() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (arr[i][j] == BLOCKED) {
                    std::cout << " % ";
                } else {
                    std::cout << "  "; 
                }
            }
            std::cout << "\n";
        }
    } //just for loop the original 2d array
};
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

    vector<pair<int, int>> computeFrontierCells(pair<int, int> cell) {
        pair<int, int> top = {arr[cell.first - 2], arr[cell.second]};
        pair<int, int> right = {arr[cell.first], arr[cell.second + 2]};
        pair<int, int> bottom = {arr[cell.first + 2], arr[cell.second]};
        pair<int, int> left = {arr[cell.first], arr[cell.second - 2]};
        vector<pair<int,int>> frontiers;

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

    void generateMaze() {
        /*
         * generate maze array
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

    void displayMaze(); //just for loop the original 2d array
};

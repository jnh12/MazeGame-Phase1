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

    pair<int, int> pickRandomCell() { // locates radnom cell in array (if u want to use pair outpput use .first/.second)
        srand(time(0));
        int randomRow = rand() % rows;
        int randomCol = rand() % cols;
        return {randomRow, randomCol};
    }

    vector<pair<int, int>> computeFrontierCells(pair<int, int> cell); // implement finding of frontier cells. Cell inputted as pair and then return an array that contains frontier cells

    void generateMaze(){
        /*
    WHILE LIST OF FRONTIER IS NOT EMPTY{
	-pick random value from list and set the value between frontier and random value from list to PASSAGE
	-find frontier cells of random value from list and add them to list of frontier values
	-remove frontier cell from frontier list.
	}
    */

    }

    void displayMaze(); //just for loop the original 2d array
};

#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <algorithm>
#include <queue>
#include "maze1.hpp"

using std::vector;
using std::pair;
using std::priority_queue;
using std::abs;
    
class MazeNavigator : public MazeGenerator{

    class Cell {   //nested class needed for navigating maze
    public:
        Cell* parent;
        int cost;
        pair<int, int> position;

        Cell(int x, int y): position({x,y}){}   //not sure if we need more contructing statements. we'll see as we write the code
    };

    int heuristic(pair<int, int> a, pair<int, int> b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
        // we use manhattan distance before start and end node (since we can't move diagonally)
    }


    vector<Cell*> navigateMaze() {

        priority_queue<pair<int, Cell*>> toVISIT;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        Cell* startCell = new Cell(starting.first, starting.second);
        startCell->cost = heuristic(startCell->position, ending); //starting cell has actual cost 0
        toVISIT.push({-startCell->cost, startCell}); //add starting cell to the priority queue
        std::vector<Cell*> path; //array containing order of nodes from start to end goal of shortest distance 

        path.push_back(startCell); //add first cell to path (first node is mandatorily visited in the shortest path)


        
        while (!toVISIT.empty()) {
            Cell* currentCell = toVISIT.top().second;
            toVISIT.pop();

            if (currentCell->position == ending) {
                std::cout << "Found the end cell!" << std::endl;
                //so path will only contain start node which is also the end node
                return path;
            }

            
            visited[currentCell->position.first][currentCell->position.second] = true;

            vector<pair<int, int>> neighbors = getNeighbours(currentCell->position);

            for (const auto& neighborPos : neighbors) {

                Cell* neighbor = new Cell(neighborPos.first, neighborPos.second);
                    //f = actual cost, which is 10 per step(node) + heuristic

                if (!visited[neighborPos.first][neighborPos.second]) {
                    neighbor->parent = currentCell;

                    if (neighbor->cost < currentCell->cost){  //ADD && toVISIT does not already contain a node with the same position coordinates
                        neighbor->cost = currentCell->cost + 10 + heuristic(neighbor->position, ending);
                        toVISIT.push({-neighbor->cost, neighbor});
                        path.push_back(currentCell);
                    }
                    visited[neighborPos.first][neighborPos.second] = true;  
                }
            }
        }
        return //no path was detected. return empty
    }
};



/*        // Cleanup memory
        while (!toVISIT.empty()) {
            delete toVISIT.top().second;    
            toVISIT.pop();
        }
/*    
            //i don't get the cleanup memory part. khalil pls explain

    
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
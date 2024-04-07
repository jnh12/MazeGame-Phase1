#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <algorithm>
#include <queue>
#include "MazeGenerator.hpp"

using std::vector;
using std::pair;
using std::priority_queue;
using std::abs;
    
class MazeNavigator : public MazeGenerator{

    public:

    class Cell {   //nested class needed for navigating maze
        public:
            Cell* parent;
            int cost;
            pair<int, int> position;

            Cell(int x, int y): position({x,y}){}
    };

            MazeNavigator(int r, int c) {
                rows = r;
                cols = c;
                arr.assign(rows, vector<int>(cols, BLOCKED)); //fills array with blocked
            }

        int heuristic(pair<int, int> a, pair<int, int> b) {
            return abs(a.first - b.first) + abs(a.second - b.second);
            // we use manhattan distance before start and end node (since we can't move diagonally)
        }

        void displayMaze2(const std::vector<std::vector<int>>& maze, const std::vector<std::pair<int, int>>& path) {
        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                if (maze[i][j] == 8) {
                    std::cout << "P "; // P represents the path cell
                } else {
                    std::cout << maze[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }


    void navigateMaze() {
        priority_queue<pair<int, Cell*>> toVISIT;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<pair<Cell*, Cell*>> parents;

        Cell* startCell = new Cell(starting.first, starting.second);
        startCell->cost = heuristic(startCell->position, ending); // starting cell has actual cost 0

        int g = 0; // Initialize g

        toVISIT.push({startCell->cost, startCell}); // add starting cell to the priority queue
        std::vector<pair<int, int>> path; // array containing positions of each node on the shortest path from start to end goal

        path.push_back(startCell->position); // add first cell to path (first node is mandatorily visited in the shortest path)

        while (!toVISIT.empty()) {
            Cell* currentCell = toVISIT.top().second;
            toVISIT.pop();

            g += 10;
            currentCell->cost = g + heuristic(currentCell->position, ending);

            if (currentCell->position == ending) {
                std::cout << "Found the end cell!" << std::endl;


                for (int i = path.size() - 1; i >= 0; i--) { //loop for displaying the path in reverse order (since path has nodes from goal going back to starting cell)
                    std::cout << "Shortest path is: " << path[i].first << "-" << path[i].second << std::endl;
                }

                // Clean up memory
                while (!toVISIT.empty()) {
                    delete toVISIT.top().second;
                    toVISIT.pop();
                }

        return;
    }


            visited[currentCell->position.first][currentCell->position.second] = true;

            vector<pair<int, int>> neighbors = getNeighbours(currentCell->position);

            for (const auto& neighborPos : neighbors) {
                Cell* neighbor = new Cell(neighborPos.first, neighborPos.second);

                if (!visited[neighborPos.first][neighborPos.second]) {
                    neighbor->parent = currentCell;
                    neighbor->cost = g + heuristic(neighbor->position, ending);

                    if (neighbor->cost < neighbor->parent->cost) {
                        toVISIT.push({neighbor->cost, neighbor});
                        path.push_back(neighbor->position); // Update path with neighbor position
                    }
                    visited[neighborPos.first][neighborPos.second] = true;
                }
            }
        }

        displayMaze2(arr, path); // display maze again, this time with the shortest path

        if (path.size() == 1) { // if the path array contains only the start cell
            path = {}; // empty the path since no path was found
        }

        std::cout << "Path does not exist" << "\n";
        }

    };

 
        
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
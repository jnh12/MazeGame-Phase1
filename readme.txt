Final Goal: Make a Maze Game that Generates Random mazes of size defined by user using prims algorithm, then solve the maze using A* Algorithm:

Checkpoint 1: Generate Maze of size xy using Prims Algorithm

Checkpoint 2: Traverse Maze using A* algorithm


Checkpoint 1:

1- Using an 2darray, fill array with 0 indicating that maze consists of only BLOCKED state
2- Locate frontier

	-find random cell in array, and set to PASSAGE
	-compute frontier cells of random cell and add to a list and change to PASSAGE (frontier cell ya3ne cell with distance 2 in either x or y direction in the array and has to be in state BLOCKED) 

	WHILE LIST OF FRONTIER IS NOT EMPTY{
	-pick random value from list and set the value between frontier and random value from list to PASSAGE
	-find frontier cells of random value from list and add them to list of frontier values
	-remove frontier cell from frontier list.
	}

3- Display the array as a sequence of cells BLOCKED and PASSAGE


hala2 the meothods like find frontier or add frontier to list or pick random value w hek we will do them kil wahad la7al then we can combine our work

testbranch test

test branch test 2


Checkpoint 2:

we use manhattan distance before start and end node (since we can't move diagonally)
        d = abs(x1 - x0) + abs(y1 - y0)
1- we build cost map:
            cost F = distance from starting node + distance from end node
                   = G                           +  H (heuristic)
                   
moving from each cell forward, backward, to left or right costs 10 each. 

2- node list of path to the goal cell. we add nodes (of class Cell) to the list one by one as we discover which is the lowest cost from each previous node.
we start by the starting cell which we initiate as our starting Cell with its respective positions

3- we create 2 other lists of nodes as arrays of Cells:
 - TOvisit[] aka neighbors list //priority queue. first Cell in first Cell out to process. out first cell to be added to this queued is our starting Cell
 - visited[] //all the Cells we have visited and are done with
  
4- when we push the Cells from Tovisit[]:
 -check if cost of the next node to be pushed(visited) is lower than our current node.
  if yes, make it the current node
 -add this node to the visited[] list and remove it from TOvisit
 -check if our current Cell is the ending Cell (compare position pairs of each)
 if yes, done

            *remember to add nodes to TOvisit list only if its position is not alr in the list OR cost is lower than previously added node for same position
            (since we might visit same node twice as part of 2 different paths. must find which is shorter)

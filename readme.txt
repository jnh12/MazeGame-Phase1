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
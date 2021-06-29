#include "robohood4.h"

void initialize()
{
	printf("\n ---------------------------> initializing for map : %d <----------------------------------  ",map);
	for (int i = 0; i < 200; i++)
	{
		visitedNode[i] = 0;
	}
	for (int i = 0; i < 200; i++)
	{
		parentNode[i] = 0;
	}
	for (int i = 0; i < 200; i++)
	{
		queue[i] = 0;
	}
	for (int i = 0; i < 200; i++)
	{
		path[i] = 0;
	}
	for (int i = 0; i < 200; i++)
	{
		returnPath[i] = 0;
	}

	found = 0;
	counter = 1;
	currentNode = 0;
	indexQ = 0;
	Path = 0;
	goTarget = 0;
	goInitial = 0;
	currentPosition = 0;
	nextPosition = 0;
	next = 1;
	current = 0;
	direction = 0;
	TargetNode = 0;
	currentSurface = 0;
}

//to detect obstacle
int ifObstacle(char obstacle)
{
	if (obstacle == '*')
	{
		return 1;
	}
	return 0;
}

//for debugging
void check()
{
	for (int i = 0; i < 200; i++)
	{
		printf("\n visitednode %d ", visitedNode[i]);
	}
	for (int i = 0; i < 200; i++)
	{
		printf("\n parentnode %d ", parentNode[i]);
	}
	for (int i = 0; queue[i] != '\0'; i++)
	{
		printf("\n queue %d ", queue[i]);
	}
}

//find path 
void findReversePath()
{
	returnPath[0] = TargetNode;
	int CurrentNode = TargetNode;

	for (int x = 1; CurrentNode != RobotNode; x++) {
		returnPath[x] = parentNode[CurrentNode];
		CurrentNode = returnPath[x];
	}
}

//find path (reversed)
void findPath()
{
	int FoundIndex=0;
	path[0] = RobotNode;
	int temp = '\0';

	for (int i = 0; returnPath[i] != 0; i++)
	{
		if (returnPath[i] == RobotNode)
		{
			FoundIndex = i;
			break;
		}
	}

	for (int j = FoundIndex, k = 0; j >= 0; j--, k++)
	{
		temp = returnPath[j];
		path[k] = temp;
	}
}
 
int move(char* world, int map_id)
{
	if (map_id != map)
	{
		map = map_id;
		initialize();
	}
	//find path
	if (Path == 0)
	{
		initialize();
		//find R and T location
		for (; world[currentNode] != 'R'; currentNode++) {}
		RobotNode = currentNode;

		for (; world[TargetNode] != 'T' && TargetNode < 147; TargetNode++) {}
		if (TargetNode == 147)
		{
			TargetNode = 0;
			for (; world[TargetNode] != 't' && TargetNode < 147; TargetNode++) {}
		}

		//initial positio parent is null(robot position)
		parentNode[currentNode] = '\0';
		//put current node into que node
		queue[indexQ++] = currentNode;


		while (target != found)
		{
			//set current node as visited note
			visitedNode[currentNode] = visited;

			//check neighbour
			for (int direction = 0; direction < 4; direction++)
			{
				if (world[currentNode + neighbour[direction]] != '#'  /* && world[currentNode + neighbour[direction]] != '*'*/ && visitedNode[currentNode + neighbour[direction]] == notVisited)
				{
					//put neighbour in queue
					queue[indexQ++] = currentNode + neighbour[direction];

					//set node to visited node
					visitedNode[currentNode + neighbour[direction]] = visited;
					//store parent node for neighbour node
					parentNode[currentNode + neighbour[direction]] = currentNode;

					//stop if T is found
					if (world[currentNode + neighbour[direction]] == 'T' || world[currentNode + neighbour[direction]] == 't')
					{
						found = 1;
						break;
					}
				}
			}
			//move to next node in queue
			currentNode = queue[counter++];
		}
		findReversePath();
		findPath();
		Path = 1;
	}

	//Return direction to robot to go to target
	if (goTarget == 0)
	{
		currentPosition = path[current++];
		printf("\n current positiion %d", currentPosition);
		nextPosition = path[next++];
		//printf("\n next %d", next);
		//printf("\n next %d", next-1);

		printf("\n next positiion %d", nextPosition);
		direction = currentPosition - nextPosition;
		printf("\n direction %d", direction);
		if (direction == east)
		{
			printf("\n right \n");
			//change move method if needed
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return changeMethod;
			}

			//detroy obstacle
			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroyEast;
			}
			return moveEast;
		}
		else if (direction == west)
		{
			printf("\n left \n");
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return 5;
			}
			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroyWest;
			}
			return moveWest;
		}
		else if (direction == south)
		{
			printf("\n below \n");
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return 5;
			}
			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroySouth;
			}
			return moveSouth;
		}
		else if (direction == north)
		{
			printf("\n up \n");
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return 5;
			}
			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroyNorth;
			}
			return moveNorth;
		}
		goTarget = 1;
		// reset for future use
		currentPosition = 0;
		nextPosition = 0;
		current = 0;
		next = 1;
	}

	//Return direction to robot to go to initial position
	if (goInitial == 0)
	{
		currentPosition = returnPath[current++];
		printf("\n current positiion %d", currentPosition);
		nextPosition = returnPath[next++];
		printf("\n next positiion %d", nextPosition);
		direction = currentPosition - nextPosition;
		printf("\n direction %d", direction);
		if (direction == east)
		{
			printf("\n right \n");
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return 5;
			}
			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroyEast;
			}
			return moveEast;
		}
		else if (direction == west)
		{
			printf("\n left \n");
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return 5;
			}

			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroyWest;
			}
			return moveWest;

		}
		else if (direction == south)
		{
			printf("\n below \n");
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return 5;
			}
			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroySouth;
			}
			return moveSouth;
		}
		else if (direction == north)
		{
			printf("\n up \n");
			if ((currentSurface == land && world[nextPosition] == '~') || (currentSurface == water && world[nextPosition] == 'O'))
			{
				if (currentSurface == land)
				{
					currentSurface = water;
				}
				else if (currentSurface == water)
				{
					currentSurface = land;
				}
				next -= 1;
				current -= 1;
				return 5;
			}
			if (ifObstacle(world[nextPosition]))
			{
				next -= 1;
				current -= 1;
				return destroyNorth;
			}
			return moveNorth;
		}
	}
}



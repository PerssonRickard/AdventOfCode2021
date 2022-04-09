#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_N_NODES_IN_PATH 100
#define MAX_N_UNIQUE_VISITED_NODES 20
#define MAX_N_PATHS 200000

typedef struct nodeInfoS
{
	char name[10];
	int id;
	int nEdges;
	int edges[10];
} nodeInfoS;

nodeInfoS nodeToInfo[20];
int nUniqueNodes = 0;
int nextBigID = 1;
int nextSmallID = -1;

void problem1();
void problem2();

void addNodeToVisited(int nodeID, int pathIndex);
void addNodeToPath(int nodeID, int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex);
void copyPath(int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex);
bool checkIfHasBeenVisitedBeforeInPath(int edgeId, int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex);
int getIndexFromId(int id);
int getLastIdInPath(int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex);
void printAllPaths();

bool checkIfHasBeenVisitedBeforeInPathOrFirstTwice(int edgeId, int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex);

bool checkIfNewNode(char name[255]);
void addUniqueNode(char name[255]);
void addEdge(char node[255], char edge[255]);

int paths[MAX_N_PATHS][MAX_N_NODES_IN_PATH] = { 0 };
int nPaths = 0;
int nPathsNextIteration = 0;
int visitedNodesInPath[MAX_N_PATHS][MAX_N_UNIQUE_VISITED_NODES] = { 0 };

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	FILE *filePointer;
	char buffer[255];

	fopen_s(&filePointer, "input.txt", "r");

	// Load the data
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);

		char firstCave[255] = { 0 };
		char secondCave[255] = { 0 };
		short isSecondCave = 0;

		int i = 0;
		int i1 = 0;
		int i2 = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '-')
			{
				isSecondCave = 1;
				i++;
				continue;
			}

			if (!isSecondCave)
			{
				firstCave[i1] = buffer[i];
				i1++;
			}
			else
			{
				secondCave[i2] = buffer[i];
				i2++;
			}
			i++;
		}

		if (checkIfNewNode(firstCave))
		{
			addUniqueNode(firstCave);
		}
		if (checkIfNewNode(secondCave))
		{
			addUniqueNode(secondCave);
		}

		addEdge(firstCave, secondCave);
		addEdge(secondCave, firstCave);
	}


	// Start from start and follow every path available in the tree
	int startId = 1000;
	int endId = 1001;
	int deadEnd = 1002;
	paths[0][0] = startId;
	nPaths = 1;
	nPathsNextIteration = 1;
	bool allPathsCompleted = false;
	while (!allPathsCompleted)
	{
		allPathsCompleted = true;
		for (int i = 0; i < nPaths; i++)
		{
			bool noEdgeAvailableInPath = true;

			// Get the id of the last node in the path
			int lastId = getLastIdInPath(paths, i);

			// If the last node is the end-node (or a dead end), then
			// skip to next path since this path is already completed
			if (lastId == endId || lastId == deadEnd)
			{
				continue;
			}
			allPathsCompleted = false;

			// Determine what node it is
			int iNode = getIndexFromId(lastId);

			// Iterate over all edges from the node
			int nNodesVisited = 0;
			for (int iEdge = 0; iEdge < nodeToInfo[iNode].nEdges; iEdge++)
			{
				// If the node is not (small and has been visited before) and is not the start node, then visit it
				if ( !(nodeToInfo[iNode].edges[iEdge] < 0 && checkIfHasBeenVisitedBeforeInPath(nodeToInfo[iNode].edges[iEdge], paths, i)) && 
					nodeToInfo[iNode].edges[iEdge] != startId)
				{
					noEdgeAvailableInPath = false;

					if (nNodesVisited == 0)
					{
						addNodeToPath(nodeToInfo[iNode].edges[iEdge], paths, i); // i since we want to reuse the already existing path
						addNodeToVisited(nodeToInfo[iNode].edges[iEdge], i);
					}
					else
					{
						copyPath(paths, i);
						addNodeToPath(nodeToInfo[iNode].edges[iEdge], paths, nPathsNextIteration); // nPathsNextIteration since we can't
																								   // reuse the already existing path
						addNodeToVisited(nodeToInfo[iNode].edges[iEdge], nPathsNextIteration);
						nPathsNextIteration++;
					}

					nNodesVisited++;
				}
			}
			if (noEdgeAvailableInPath)
			{
				// The path is a dead end, indicate by node id deadEnd (1002)
				addNodeToPath(deadEnd, paths, i);
			}
		}
		nPaths = nPathsNextIteration;
	}

	// Print all paths
	//printAllPaths();

	int nPathsVisitSmallNodeAtMostOnce = 0;
	int nValidPaths = 0;
	// Count number of paths that visit small nodes at most once
	for (int i = 0; i < nPaths; i++)
	{
		bool validPath = true;
		bool smallNodeAlreadyVisited = false;
		bool smallNodeVisitedAtMostOnce = true;
		int j = 0;
		while (paths[i][j] != 0)
		{
			if (paths[i][j] == 1002)
			{
				validPath = false;
			}
			if (paths[i][j] < 0 && smallNodeAlreadyVisited)
			{
				smallNodeVisitedAtMostOnce = false;
			}
			if (paths[i][j] < 0)
			{
				smallNodeAlreadyVisited = true;
			}
			j++;
		}
		if (validPath && smallNodeVisitedAtMostOnce)
		{
			nPathsVisitSmallNodeAtMostOnce++;
		}
		if (validPath)
		{
			nValidPaths++;
		}
	}

	printf("\nAnswer: %d. Also number of valid paths: %d \n", nPathsVisitSmallNodeAtMostOnce, nValidPaths);

	fclose(filePointer);
}

void addNodeToVisited(int nodeID, int pathIndex)
{
	int i = 0;

	// Check if not already in visitedNodes array
	bool alreadyInArray = false;
	while (visitedNodesInPath[pathIndex][i] != 0)
	{
		if (visitedNodesInPath[pathIndex][i] == nodeID)
		{
			alreadyInArray = true;
			break;
		}
		i++;
	}

	if (!alreadyInArray)
	{
		visitedNodesInPath[pathIndex][i] = nodeID;
	}
}

void addNodeToPath(int nodeID, int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex)
{
	int i = 0;
	while (currentPaths[pathIndex][i] != 0)
	{
		i++;
	}
	currentPaths[pathIndex][i] = nodeID;
}

void copyPath(int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex)
{
	int i = 0;
	while (currentPaths[pathIndex][i+1] != 0)
	{
		currentPaths[nPathsNextIteration][i] = currentPaths[pathIndex][i];
		i++;
	}
}

bool checkIfHasBeenVisitedBeforeInPath(int edgeId, int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex)
{
	bool visitedBefore = false;
	for (int i = 0; i < MAX_N_UNIQUE_VISITED_NODES; i++)
	{
		if (edgeId == currentPaths[pathIndex][i])
		{
			visitedBefore = true;
			break;
		}
	}

	return visitedBefore;
}

void printAllPaths()
{
	for (int i = 0; i < nPaths; i++)
	{
		int j = 0;
		while (paths[i][j] != 0)
		{
			if (paths[i][j + 1] != 0)
			{
				//printf("%d,", paths[i][j]);
				switch (paths[i][j])
				{
				case 1000:
					printf("start");
					break;
				case 1:
					printf("A");
					break;
				case -1:
					printf("b");
					break;
				case -2:
					printf("c");
					break;
				case -3:
					printf("d");
					break;
				case 1001:
					printf("end");
					break;
				case 1002:
					printf("NOT VALID (DEAD END)");
					break;
				}
				printf(",");
			}
			else
			{
				//printf("%d", paths[i][j]);
				switch (paths[i][j])
				{
				case 1000:
					printf("start");
					break;
				case 1:
					printf("A");
					break;
				case -1:
					printf("b");
					break;
				case -2:
					printf("c");
					break;
				case -3:
					printf("d");
					break;
				case 1001:
					printf("end");
					break;
				case 1002:
					printf("NOT VALID (DEAD END)");
					break;
				}
			}
			j++;
		}
		printf("\n");
	}
}

void problem2()
{
	FILE *filePointer;
	char buffer[255];

	fopen_s(&filePointer, "input.txt", "r");

	// Load the data
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);

		char firstCave[255] = { 0 };
		char secondCave[255] = { 0 };
		short isSecondCave = 0;

		int i = 0;
		int i1 = 0;
		int i2 = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '-')
			{
				isSecondCave = 1;
				i++;
				continue;
			}

			if (!isSecondCave)
			{
				firstCave[i1] = buffer[i];
				i1++;
			}
			else
			{
				secondCave[i2] = buffer[i];
				i2++;
			}
			i++;
		}

		if (checkIfNewNode(firstCave))
		{
			addUniqueNode(firstCave);
		}
		if (checkIfNewNode(secondCave))
		{
			addUniqueNode(secondCave);
		}

		addEdge(firstCave, secondCave);
		addEdge(secondCave, firstCave);
	}


	// Start from start and follow every path available in the tree
	int startId = 1000;
	int endId = 1001;
	int deadEnd = 1002;
	paths[0][0] = startId;
	nPaths = 1;
	nPathsNextIteration = 1;
	bool allPathsCompleted = false;
	while (!allPathsCompleted)
	{
		allPathsCompleted = true;
		for (int i = 0; i < nPaths; i++)
		{
			bool noEdgeAvailableInPath = true;

			// Get the id of the last node in the path
			int lastId = getLastIdInPath(paths, i);

			// If the last node is the end-node (or a dead end), then
			// skip to next path since this path is already completed
			if (lastId == endId || lastId == deadEnd)
			{
				continue;
			}
			allPathsCompleted = false;

			// Determine what node it is
			int iNode = getIndexFromId(lastId);

			bool hasPathBeenToSmallNodeTwice = checkIfPathBeenToSmallNodeTwice(paths, i);

			// Iterate over all edges from the node
			int nNodesVisited = 0;
			for (int iEdge = 0; iEdge < nodeToInfo[iNode].nEdges; iEdge++)
			{
				// If the node is not (small and has been visited before) and is not the start node, then visit it
				bool shouldVisit = !(nodeToInfo[iNode].edges[iEdge] < 0 && checkIfHasBeenVisitedBeforeInPath(nodeToInfo[iNode].edges[iEdge], paths, i)) ||
					!hasPathBeenToSmallNodeTwice;
				if (shouldVisit && nodeToInfo[iNode].edges[iEdge] != startId)
				{
					noEdgeAvailableInPath = false;

					if (nNodesVisited == 0)
					{
						addNodeToPath(nodeToInfo[iNode].edges[iEdge], paths, i); // i since we want to reuse the already existing path
						addNodeToVisited(nodeToInfo[iNode].edges[iEdge], i);
					}
					else
					{
						copyPath(paths, i);
						addNodeToPath(nodeToInfo[iNode].edges[iEdge], paths, nPathsNextIteration); // nPathsNextIteration since we can't
																								   // reuse the already existing path
						addNodeToVisited(nodeToInfo[iNode].edges[iEdge], nPathsNextIteration);
						nPathsNextIteration++;
					}

					nNodesVisited++;
				}
			}
			if (noEdgeAvailableInPath)
			{
				// The path is a dead end, indicate by node id deadEnd (1002)
				addNodeToPath(deadEnd, paths, i);
			}
		}
		nPaths = nPathsNextIteration;
	}

	// Print all paths
	//printAllPaths();

	int nPathsVisitSmallNodeAtMostOnce = 0;
	int nValidPaths = 0;
	// Count number of paths that visit small nodes at most once
	for (int i = 0; i < nPaths; i++)
	{
		bool validPath = true;
		int j = 0;
		while (paths[i][j] != 0)
		{
			if (paths[i][j] == 1002)
			{
				validPath = false;
			}
			j++;
		}

		if (validPath)
		{
			nValidPaths++;
		}
	}

	printf("\nAnswer: %d. Also number of valid paths: %d \n", nPathsVisitSmallNodeAtMostOnce, nValidPaths);

	fclose(filePointer);
}

checkIfPathBeenToSmallNodeTwice(int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex)
{
	bool firstSmallNodeVisitedTwice = false;

	int nTimesVisited[MAX_N_NODES_IN_PATH] = { 0 };
	int i = 0;

	int test[MAX_N_NODES_IN_PATH] = { 0 };
	while (currentPaths[pathIndex][i] != 0)
	{
		test[i] = currentPaths[pathIndex][i];
		i++;
	}

	i = 0;
	while (currentPaths[pathIndex][i] != 0)
	{
		int j = 0;
		while (currentPaths[pathIndex][j] != 0)
		{
			if (currentPaths[pathIndex][i] == currentPaths[pathIndex][j])
			{
				nTimesVisited[i]++;
				if (nTimesVisited[i] > 1 && currentPaths[pathIndex][i] < 0)
				{
					firstSmallNodeVisitedTwice = true;
					break;
				}
			}
			j++;
		}

		if (firstSmallNodeVisitedTwice)
		{
			break;
		}
		i++;
	}

	return firstSmallNodeVisitedTwice;
}



int getIndexFromId(int id)
{
	int index = -1;
	for (int i = 0; i < nUniqueNodes; i++)
	{
		if (nodeToInfo[i].id == id)
		{
			index = i;
			break;
		}
	}

	return index;
}

int getLastIdInPath(int currentPaths[MAX_N_PATHS][MAX_N_NODES_IN_PATH], int pathIndex)
{
	int i = 0;
	while (currentPaths[pathIndex][i] != 0)
	{
		i++;
	}

	if (i > 0)
	{
		i--;
	}

	return currentPaths[pathIndex][i];
}

bool checkIfNewNode(char name[255])
{
	int j = 0;
	bool isNew = 1;
	for (int i = 0; i < nUniqueNodes; i++)
	{
		isNew = 0;
		while (name[j] != 0)
		{
			if (name[j] != nodeToInfo[i].name[j])
			{
				isNew = 1;
				break;
			}
			j++;
		}

		if (!isNew)
		{
			break;
		}
	}

	return isNew;
}

void addUniqueNode(char name[255])
{
	short isSmallCave = 1;

	int i = 0;
	while (name[i] != 0)
	{
		nodeToInfo[nUniqueNodes].name[i] = name[i];

		if (isupper(name[i]))
		{
			isSmallCave = 0;
		}
		i++;
	}


	// Assign special id if the node is start (1000) or end (1001)
	char startName[6] = { 's', 't', 'a', 'r', 't', '\0' };
	char endName[4] = { 'e', 'n', 'd', '\0' };
	i = 0;
	bool isStart = 1;
	bool isEnd = 1;
	while (name[i] != 0)
	{
		if (name[i] != startName[i])
		{
			isStart = 0;
		}
		if (name[i] != endName[i])
		{
			isEnd = 0;
		}
		i++;
	}


	if (isStart)
	{
		nodeToInfo[nUniqueNodes].id = 1000;
	}
	else if (isEnd)
	{
		nodeToInfo[nUniqueNodes].id = 1001;
	}
	else
	{
		if (isSmallCave)
		{
			nodeToInfo[nUniqueNodes].id = nextSmallID;
			nextSmallID--;
		}
		else
		{
			nodeToInfo[nUniqueNodes].id = nextBigID;
			nextBigID++;
		}
	}

	nUniqueNodes++;
}

void addEdge(char node[255], char edge[255])
{
	int nodeIndex = -1;
	for (int i = 0; i < nUniqueNodes; i++)
	{
		nodeIndex = i;

		int j = 0;
		while (node[j] != 0)
		{
			if (node[j] != nodeToInfo[i].name[j])
			{
				nodeIndex = -1;
				break;
			}
			j++;
		}

		if (nodeIndex != -1)
		{
			break;
		}
	}

	int edgeID;
	bool edgeIdFound = 0;
	for (int i = 0; i < nUniqueNodes; i++)
	{
		edgeID = nodeToInfo[i].id;
		edgeIdFound = 1;

		int j = 0;
		while (edge[j] != 0)
		{
			if (edge[j] != nodeToInfo[i].name[j])
			{
				edgeIdFound = 0;
				break;
			}
			j++;
		}

		if (edgeIdFound)
		{
			break;
		}
	}

	nodeToInfo[nodeIndex].edges[nodeToInfo[nodeIndex].nEdges] = edgeID;
	nodeToInfo[nodeIndex].nEdges++;
}
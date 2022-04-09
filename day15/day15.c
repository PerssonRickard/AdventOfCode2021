#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void problem1();
void problem2();

#define MAX_N_NODES 300000
#define MAP_WIDTH 500
#define MAP_HEIGHT 500

typedef struct nodeS nodeS;

struct nodeS
{
	int nodeId;
	int xPos;
	int yPos;
	int distance;
	bool hasBeenVisited;
	nodeS* prevNode;
};

typedef struct linkedListNodeS linkedListNodeS;

struct linkedListNodeS
{
	nodeS* node;
	linkedListNodeS* next;
};

void printQueue();
void visitEdges(nodeS* currentNode, int edgeIds[4][2], int nEdges);
void visitEdges2(nodeS* currentNode, int edgeIds[4][2], int nEdges);
void getAllEdgeIds(nodeS* currentNode, int edgeIds[4][2], int* nEdges);
nodeS* getSeenNode(int x, int y);
int findShortestNode(nodeS** shortestNode);
void addSeenNode(nodeS* node);

nodeS* seenNodes[MAP_WIDTH][MAP_HEIGHT];
linkedListNodeS* queue = NULL;
int map[MAP_WIDTH][MAP_HEIGHT];
int map2[5*MAP_WIDTH][5*MAP_HEIGHT];

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

	int x = 0;
	int y = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);

		x = 0;
		while (buffer[x] != 0)
		{
			map[x][y] = buffer[x] - '0';
			x++;
		}
		y++;
	}

	// Start at top-left node
	nodeS* startNode = malloc(sizeof(nodeS));
	startNode->distance = 0;
	startNode->nodeId = 0;
	startNode->xPos = 0;
	startNode->yPos = 0;
	startNode->hasBeenVisited = false;
	startNode->prevNode = NULL;

	// Add end-node so that it can be used as while-loop-condition
	nodeS* endNode = malloc(sizeof(nodeS));
	endNode->distance = 1000001;
	endNode->xPos = MAP_WIDTH - 1;
	endNode->yPos = MAP_HEIGHT - 1;
	endNode->hasBeenVisited = false;
	endNode->prevNode = NULL;

	addSeenNode(startNode);
	addSeenNode(endNode);

	nodeS* currentNode = NULL;
	int minNodeDistance = 1000000;
	while (endNode->distance > minNodeDistance)
	{
		//printQueue();
		minNodeDistance = findShortestNode(&currentNode);

		currentNode->hasBeenVisited = true;

		int edgeIds[4][2];
		int nEdges;
		getAllEdgeIds(currentNode, edgeIds, &nEdges);
		visitEdges(currentNode, edgeIds, nEdges);
	}

	/*currentNode = endNode->prevNode;
	while (currentNode != NULL)
	{
		//printf("%d ", currentNode->distance);
		printf("%d,%d ", currentNode->xPos, currentNode->yPos);
		currentNode = currentNode->prevNode;
	}*/

	/*for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (seenNodes[x][y] != NULL)
			{
				currentNode = seenNodes[x][y];
				printf("Node %d,%d: %d\n", currentNode->xPos, currentNode->yPos, currentNode->distance);
			}
		}
	}*/

	printf("\nAnswer: %d\n", endNode->distance);

	fclose(filePointer);
}

void printQueue()
{
	linkedListNodeS* currentQueueNode = queue;
	printf("\n");
	while (currentQueueNode != NULL)
	{
		printf("Node %d,%d: %d\n", currentQueueNode->node->xPos, currentQueueNode->node->yPos, currentQueueNode->node->distance);
		currentQueueNode = currentQueueNode->next;
	}
}

void visitEdges(nodeS* currentNode, int edgeIds[4][2], int nEdges)
{
	nodeS* node = NULL;
	int x;
	int y;
	int edgeDistance;
	int distanceFromStart;
	bool newNode = false;
	for (int i = 0; i < nEdges; i++)
	{
		x = edgeIds[i][0];
		y = edgeIds[i][1];

		node = getSeenNode(x, y);

		if (node != NULL)
		{
			if (node->hasBeenVisited)
			{
				continue;
			}
		}
		else
		{
			// allocate memory
			node = malloc(sizeof(nodeS));
			node->distance = -1;
			node->nodeId = y*10 + x;
			node->xPos = x;
			node->yPos = y;
			node->hasBeenVisited = false;
			node->prevNode = NULL;

			newNode = true;
		}

		edgeDistance = map[x][y];
		distanceFromStart = currentNode->distance + edgeDistance;
		if (distanceFromStart < node->distance || node->distance == -1)
		{
			node->distance = distanceFromStart;
			node->prevNode = currentNode;
		}

		if (newNode)
		{
			addSeenNode(node);
		}
	}
}

void visitEdges2(nodeS* currentNode, int edgeIds[4][2], int nEdges)
{
	nodeS* node = NULL;
	int x;
	int y;
	int edgeDistance;
	int distanceFromStart;
	bool newNode = false;
	for (int i = 0; i < nEdges; i++)
	{
		x = edgeIds[i][0];
		y = edgeIds[i][1];

		node = getSeenNode(x, y);

		if (node != NULL)
		{
			if (node->hasBeenVisited)
			{
				continue;
			}
		}
		else
		{
			// allocate memory
			node = malloc(sizeof(nodeS));
			node->distance = -1;
			node->nodeId = y * 10 + x;
			node->xPos = x;
			node->yPos = y;
			node->hasBeenVisited = false;
			node->prevNode = NULL;

			newNode = true;
		}

		edgeDistance = map2[x][y];
		distanceFromStart = currentNode->distance + edgeDistance;
		if (distanceFromStart < node->distance || node->distance == -1)
		{
			node->distance = distanceFromStart;
			node->prevNode = currentNode;
		}

		if (newNode)
		{
			addSeenNode(node);
		}
	}
}

void getAllEdgeIds(nodeS* currentNode, int edgeIds[4][2], int* nEdges)
{
	int x = 0;
	int y = 0;
	*nEdges = 0;

	// Left
	if (currentNode->xPos > 0) 
	{
		x = currentNode->xPos - 1;
		y = currentNode->yPos;
		edgeIds[*nEdges][0] = x;
		edgeIds[*nEdges][1] = y;
		(*nEdges)++;
	}
	// Right
	if (currentNode->xPos < MAP_WIDTH - 1)
	{
		x = currentNode->xPos + 1;
		y = currentNode->yPos;
		edgeIds[*nEdges][0] = x;
		edgeIds[*nEdges][1] = y;
		(*nEdges)++;
	}
	// Up
	if (currentNode->yPos > 0)
	{
		x = currentNode->xPos;
		y = currentNode->yPos - 1;
		edgeIds[*nEdges][0] = x;
		edgeIds[*nEdges][1] = y;
		(*nEdges)++;
	}
	// Down
	if (currentNode->yPos < MAP_HEIGHT - 1)
	{
		x = currentNode->xPos;
		y = currentNode->yPos + 1;
		edgeIds[*nEdges][0] = x;
		edgeIds[*nEdges][1] = y;
		(*nEdges)++;
	}
}

nodeS* getSeenNode(int x, int y)
{
	return seenNodes[x][y];
}

int findShortestNode(nodeS** shortestNode)
{
	// Find the node with shortest distance that has not already been visited
	int shortestDistance = -1;
	if (queue->node != NULL)
	{
		shortestDistance = queue->node->distance;
		*shortestNode = queue->node;

		// Remove node from top of queue
		queue = queue->next;
	}

	return shortestDistance;
}

void addSeenNode(nodeS* node)
{
	seenNodes[node->xPos][node->yPos] = node;

	// Add to queue
	if (queue == NULL)
	{
		queue = malloc(sizeof(linkedListNodeS));
		queue->node = node;
		queue->next = NULL;
	}
	else
	{
		linkedListNodeS* newQueueElement = malloc(sizeof(linkedListNodeS));
		newQueueElement->node = node;

		int distance = node->distance;
		linkedListNodeS* prevQueueElement = NULL;
		linkedListNodeS* currentQueueElement = queue;
		while (currentQueueElement->node->distance <= distance && currentQueueElement->node->distance != -1)
		{
			prevQueueElement = currentQueueElement;
			currentQueueElement = currentQueueElement->next;
			if (currentQueueElement == NULL)
			{
				break;
			}
		}

		// node should be inserted before currentQueueElement
		if (currentQueueElement != NULL)
		{
			if (prevQueueElement == NULL) // Insert at start of queue
			{
				newQueueElement->next = currentQueueElement;
				queue = newQueueElement;
			}
			else // Insert in queue
			{
				newQueueElement->next = currentQueueElement;
				prevQueueElement->next = newQueueElement;
			}
		}
		else // node should be inserted after currentQueueElement at end of queue
		{
			newQueueElement->next = NULL;
			prevQueueElement->next = newQueueElement;
		}
	}
}

void problem2()
{
	FILE *filePointer;
	char buffer[255];

	fopen_s(&filePointer, "input.txt", "r");

	int x = 0;
	int y = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);

		x = 0;
		while (buffer[x] != 0)
		{
			for (int y2 = 0; y2 < 5; y2++)
			{
				for (int x2 = 0; x2 < 5; x2++)
				{
					int risk = buffer[x] - '0' + x2 + y2;
					if (risk > 9)
					{
						risk = risk % 9;
					}

					map2[x + x2*100][y + y2*100] = risk; // 100 is the previous map width and height, can be handled better
				}
			}
			x++;
		}
		y++;
	}

	// Start at top-left node
	nodeS* startNode = malloc(sizeof(nodeS));
	startNode->distance = 0;
	startNode->nodeId = 0;
	startNode->xPos = 0;
	startNode->yPos = 0;
	startNode->hasBeenVisited = false;
	startNode->prevNode = NULL;

	// Add end-node so that it can be used as while-loop-condition
	nodeS* endNode = malloc(sizeof(nodeS));
	endNode->distance = 1000001;
	endNode->xPos = 100*5 - 1; // 100 is the previous map width and height, can be handled better
	endNode->yPos = 100*5 - 1; // 100 is the previous map width and height, can be handled better
	endNode->hasBeenVisited = false;
	endNode->prevNode = NULL;

	addSeenNode(startNode);
	addSeenNode(endNode);

	nodeS* currentNode = NULL;
	int minNodeDistance = 1000000;
	while (endNode->distance > minNodeDistance && minNodeDistance != -1)
	{
		minNodeDistance = findShortestNode(&currentNode);
		currentNode->hasBeenVisited = true;

		int edgeIds[4][2];
		int nEdges;
		getAllEdgeIds(currentNode, edgeIds, &nEdges);
		visitEdges2(currentNode, edgeIds, nEdges);
	}

	/*currentNode = endNode->prevNode;
	while (currentNode != NULL)
	{
		//printf("%d ", currentNode->distance);
		printf("%d,%d ", currentNode->xPos, currentNode->yPos);
		currentNode = currentNode->prevNode;
	}*/

	printf("\nAnswer: %d\n", endNode->distance);

	fclose(filePointer);
}
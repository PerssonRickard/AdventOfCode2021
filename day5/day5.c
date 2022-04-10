#include <stdio.h>
#include <string.h>

#define gridWidth 1000
#define gridHeight 1000

int grid[gridWidth][gridHeight] = { 0 };
int grid2[gridWidth][gridHeight] = { 0 };

void problem1();
void problem2();
void printLargestCoordinates();

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	//char buffer[255];
	int x1, y1, x2, y2 = -1;

	FILE *filePointer = fopen("input.txt", "r");

	while (fscanf(filePointer, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4)
	{
		printf("%d,%d -> %d,%d\n", x1, y1, x2, y2);

		if (x1 == x2) // horizontal line
		{
			if (y1 < y2)
			{
				for (int i = y1; i <= y2; i++)
				{
					grid[x1][i]++;
				}
			}
			else
			{
				for (int i = y2; i <= y1; i++)
				{
					grid[x1][i]++;
				}
			}
		}
		else if (y1 == y2) // vertical line
		{
			if (x1 < x2)
			{
				for (int i = x1; i <= x2; i++)
				{
					grid[i][y1]++;
				}
			}
			else
			{
				for (int i = x2; i <= x1; i++)
				{
					grid[i][y1]++;
				}
			}
		}
		// else diagonal line
	}

	// Count number of points where atleast two lines overlap
	int count = 0;
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (grid[x][y] >= 2)
			{
				count++;
			}
		}
	}

	printf("\nAnswer: %d\n", count);

	fclose(filePointer);
}

void problem2()
{
	//char buffer[255];
	int x1, y1, x2, y2 = -1;
	int deltaX, deltaY;

	FILE *filePointer = fopen("input.txt", "r");

	while (fscanf(filePointer, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4)
	{
		printf("%d,%d -> %d,%d\n", x1, y1, x2, y2);

		if (x1 < x2)
		{
			deltaX = 1;
		}
		else if (x1 > x2)
		{
			deltaX = -1;
		}
		else
		{
			deltaX = 0;
		}

		if (y1 < y2)
		{
			deltaY = 1;
		}
		else if (y1 > y2)
		{
			deltaY = -1;
		}
		else
		{
			deltaY = 0;
		}

		int ix = x1;
		int iy = y1;
		while (ix != x2 || iy != y2)
		{
			grid2[ix][iy]++;
			ix += deltaX;
			iy += deltaY;
		}
		grid2[ix][iy]++;
	}

	// Count number of points where atleast two lines overlap
	int count = 0;
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (grid2[x][y] >= 2)
			{
				count++;
			}
		}
	}

	printf("\nAnswer: %d\n", count);

	fclose(filePointer);
}

void printLargestCoordinates()
{
	int x1, y1, x2, y2 = -1;
	int largestCoordinateX = -1;
	int largestCoordinateY = -1;

	FILE *filePointer = fopen("input.txt", "r");

	while (fscanf(filePointer, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4)
	{
		if (x1 > largestCoordinateX)
		{
			largestCoordinateX = x1;
		}
		if (x2 > largestCoordinateX)
		{
			largestCoordinateX = x2;
		}
		if (y1 > largestCoordinateY)
		{
			largestCoordinateY = y1;
		}
		if (y2 > largestCoordinateY)
		{
			largestCoordinateY = y2;
		}
	}

	printf("Largest coordinateX: %d\n", largestCoordinateX);
	printf("Largest coordinateY: %d\n", largestCoordinateY);

	fclose(filePointer);
}

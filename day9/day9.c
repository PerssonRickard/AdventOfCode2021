#include <stdio.h>
#include <string.h>

#define nRows 100
#define nCols 100

void problem1();
void problem2();


typedef struct basinS
{
	int id;
	int size;
} basinS;

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	FILE *filePointer;
	char buffer[255];
	short heightmap[nCols][nRows];

	fopen_s(&filePointer, "input.txt", "r");

	int y = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		int x = 0;
		while (buffer[x] != '\0')
		{
			heightmap[x][y] = buffer[x] - '0';
			x++;
		}
		y++;

		printf("%s\n", buffer);
	}

	int sum = 0;
	for (int y = 0; y < nRows; y++)
	{
		for (int x = 0; x < nCols; x++)
		{
			short isLowPoint = 1;

			if (x - 1 >= 0)
			{
				if (heightmap[x][y] >= heightmap[x - 1][y])
				{
					isLowPoint = 0;
				}
			}
			if (x + 1 < nCols)
			{
				if (heightmap[x][y] >= heightmap[x + 1][y])
				{
					isLowPoint = 0;
				}
			}
			if (y - 1 >= 0)
			{
				if (heightmap[x][y] >= heightmap[x][y - 1])
				{
					isLowPoint = 0;
				}
			}
			if (y + 1 < nRows)
			{
				if (heightmap[x][y] >= heightmap[x][y + 1])
				{
					isLowPoint = 0;
				}
			}

			if (isLowPoint)
			{
				sum += heightmap[x][y] + 1;
			}
		}
	}

	printf("\nAnswer: %d\n", sum);

	fclose(filePointer);
}

void problem2()
{
	FILE *filePointer;
	char buffer[255];
	short heightmap[nCols][nRows];
	short basinMap[2][nCols][nRows] = {0};

	fopen_s(&filePointer, "input.txt", "r");

	int y = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		int x = 0;
		while (buffer[x] != '\0')
		{
			heightmap[x][y] = buffer[x] - '0';
			x++;
		}
		y++;

		//printf("%s\n", buffer);
	}

	int i = 0;
	int lowPointID = 1;
	for (int y = 0; y < nRows; y++)
	{
		for (int x = 0; x < nCols; x++)
		{
			short isLowPoint = 1;

			if (x - 1 >= 0)
			{
				if (heightmap[x][y] >= heightmap[x - 1][y])
				{
					isLowPoint = 0;
				}
			}
			if (x + 1 < nCols)
			{
				if (heightmap[x][y] >= heightmap[x + 1][y])
				{
					isLowPoint = 0;
				}
			}
			if (y - 1 >= 0)
			{
				if (heightmap[x][y] >= heightmap[x][y - 1])
				{
					isLowPoint = 0;
				}
			}
			if (y + 1 < nRows)
			{
				if (heightmap[x][y] >= heightmap[x][y + 1])
				{
					isLowPoint = 0;
				}
			}

			if (isLowPoint)
			{
				basinMap[i][x][y] = lowPointID;
				lowPointID++;
			}
		}
	}
	i = (i + 1) % 2;

	short sameBasinMaps = 0;
	while (!sameBasinMaps)
	{
		// Copy over to other basinMap
		for (int y = 0; y < nRows; y++)
		{
			for (int x = 0; x < nCols; x++)
			{
				basinMap[i][x][y] = basinMap[(i + 1) % 2][x][y];
			}
		}

		sameBasinMaps = 1;
		for (int y = 0; y < nRows; y++)
		{
			for (int x = 0; x < nCols; x++)
			{
				if (x - 1 >= 0 && basinMap[i][x][y])
				{
					if (heightmap[x - 1][y] != 9 && basinMap[i][x - 1][y] == 0)
					{
						basinMap[i][x - 1][y] = basinMap[i][x][y];
						sameBasinMaps = 0;
					}
				}
				if (x + 1 < nCols && basinMap[i][x][y])
				{
					if (heightmap[x + 1][y] != 9 && basinMap[i][x + 1][y] == 0)
					{
						basinMap[i][x + 1][y] = basinMap[i][x][y];
						sameBasinMaps = 0;
					}
				}
				if (y - 1 >= 0 && basinMap[i][x][y])
				{
					if (heightmap[x][y - 1] != 9 && basinMap[i][x][y - 1] == 0)
					{
						basinMap[i][x][y - 1] = basinMap[i][x][y];
						sameBasinMaps = 0;
					}
				}
				if (y + 1 < nRows && basinMap[i][x][y])
				{
					if (heightmap[x][y + 1] != 9 && basinMap[i][x][y + 1] == 0)
					{
						basinMap[i][x][y + 1] = basinMap[i][x][y];
						sameBasinMaps = 0;
					}
				}
			}
		}

		i = (i + 1) % 2;
	}

	int largestSize = 0;
	int secondLargestSize = 0;
	int thirdLargestSize = 0;
	for (int currentLowPointID = 1; currentLowPointID < lowPointID; currentLowPointID++)
	{
		int currentSize = 0;
		for (int y = 0; y < nRows; y++)
		{
			for (int x = 0; x < nCols; x++)
			{
				if (basinMap[0][x][y] == currentLowPointID)
				{
					currentSize++;
				}
			}
		}

		if (currentSize >= largestSize)
		{
			int temp = largestSize;
			largestSize = currentSize;

			int temp2 = secondLargestSize;
			secondLargestSize = temp;

			thirdLargestSize = temp2;
		}
		else if (currentSize >= secondLargestSize)
		{
			int temp = secondLargestSize;
			secondLargestSize = currentSize;
			thirdLargestSize = temp;
		}
		else if (currentSize >= thirdLargestSize)
		{
			thirdLargestSize = currentSize;
		}
	}


	printf("\nAnswer: %d * %d * %d = %d\n", largestSize, secondLargestSize, thirdLargestSize, largestSize*secondLargestSize*thirdLargestSize);

	fclose(filePointer);
}
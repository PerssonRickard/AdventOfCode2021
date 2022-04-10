#include <stdio.h>
#include <string.h>

#define MAX_N_ROWS 1000
#define MAX_N_COLS 1500

short paper[MAX_N_COLS][MAX_N_ROWS] = { 0 };

void problem1();
void problem2();

void printPaper();

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char buffer[255];

	FILE *filePointer = fopen("input.txt", "r");

	int i = 0;
	int x = 0;
	int y = 0;
	while (fscanf(filePointer, "%d,%d", &x, &y) == 2 && i < 866)
	{
		paper[x][y] = 1;
		printf("%d,%d\n", x, y);
		i++;
	}

	int j = 0;
	short foldCount = 0;
	char direction;
	int coordinate;
	int delta = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		if (j == 2)
		{
			sscanf(buffer, "%c=%d", &direction, &coordinate);
			printf("%s\n", buffer);

			if (direction == 'x')
			{
				for (y = 0; y < MAX_N_ROWS; y++)
				{
					for (x = coordinate + 1; x < MAX_N_COLS; x++) // Could be optimized by only iterating to the folded line instead of MAX_N_COLS every time
					{
						// Only need to do something if there is a point
						if (paper[x][y])
						{
							delta = x - coordinate;
							paper[coordinate - delta][y] = 1;

							// Remove the point which has been folded over
							paper[x][y] = 0;
						}
					}
				}
			}
			else if (direction == 'y')
			{
				for (y = coordinate + 1; y < MAX_N_ROWS; y++) // Could be optimized by only iterating to the folded line instead of MAX_N_ROWS every time
				{
					for (int x = 0; x < MAX_N_COLS; x++)
					{
						// Only need to do something if there is a point
						if (paper[x][y])
						{
							delta = y - coordinate;
							paper[x][coordinate - delta] = 1;

							// Remove the point which has been folded over
							paper[x][y] = 0;
						}
					}
				}
			}
			else
			{
				printf("Error, unknown direction!\n");
			}

			foldCount++;
		}

		j = (j + 1) % 3;

		// Only complete the first fold instruction
		if (foldCount == 1)
		{
			break;
		}
	}

	int dotCount = 0;
	for (y = 0; y < MAX_N_ROWS; y++)
	{
		for (x = 0; x < MAX_N_COLS; x++)
		{
			if (paper[x][y])
			{
				dotCount++;
			}
		}
	}

	printf("\nAnswer: %d\n", dotCount);

	fclose(filePointer);
}

void printPaper()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			if (paper[x][y])
			{
				printf("#");
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}
}

void problem2()
{
	char buffer[255];

	FILE *filePointer = fopen("input.txt", "r");

	int i = 0;
	int x = 0;
	int y = 0;
	while (fscanf(filePointer, "%d,%d", &x, &y) == 2 && i < 866)
	{
		paper[x][y] = 1;
		printf("%d,%d\n", x, y);
		i++;
	}

	int j = 0;
	char direction;
	int coordinate;
	int delta = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		if (j == 2)
		{
			sscanf(buffer, "%c=%d", &direction, &coordinate);
			printf("%s\n", buffer);

			if (direction == 'x')
			{
				for (y = 0; y < MAX_N_ROWS; y++)
				{
					for (x = coordinate + 1; x < MAX_N_COLS; x++) // Could be optimized by only iterating to the folded line instead of MAX_N_COLS every time
					{
						// Only need to do something if there is a point
						if (paper[x][y])
						{
							delta = x - coordinate;
							paper[coordinate - delta][y] = 1;

							// Remove the point which has been folded over
							paper[x][y] = 0;
						}
					}
				}
			}
			else if (direction == 'y')
			{
				for (y = coordinate + 1; y < MAX_N_ROWS; y++) // Could be optimized by only iterating to the folded line instead of MAX_N_ROWS every time
				{
					for (int x = 0; x < MAX_N_COLS; x++)
					{
						// Only need to do something if there is a point
						if (paper[x][y])
						{
							delta = y - coordinate;
							paper[x][coordinate - delta] = 1;

							// Remove the point which has been folded over
							paper[x][y] = 0;
						}
					}
				}
			}
			else
			{
				printf("Error, unknown direction!\n");
			}
		}

		j = (j + 1) % 3;
	}

	printPaper();

	fclose(filePointer);
}

#include <stdio.h>
#include <string.h>

#define nRows 10
#define nCols 10

void problem1();
void problem2();
void printEnergyLevels();

typedef struct octopusS {
	int energyLevel;
	short hasFlashed;
} octopusS;

octopusS octupuses[nCols][nRows] = { 0 };

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char buffer[255];

	FILE *filePointer = fopen("input.txt", "r");

	int y = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		int x = 0;
		while (buffer[x] != '\0')
		{
			octupuses[x][y].energyLevel = buffer[x] - '0';
			x++;
		}
		y++;
		printf("%s\n", buffer);
	}

	int nTotalFlashes = 0;
	for (int stepCount = 0; stepCount < 100; stepCount++)
	{

		for (int y = 0; y < nRows; y++)
		{
			for (int x = 0; x < nCols; x++)
			{
				octupuses[x][y].hasFlashed = 0;
				octupuses[x][y].energyLevel++;
			}
		}

		short wasAChange;
		do
		{
			wasAChange = 0;
			for (int y = 0; y < nRows; y++)
			{
				for (int x = 0; x < nCols; x++)
				{
					if (octupuses[x][y].energyLevel > 9 && !octupuses[x][y].hasFlashed)
					{
						if (x - 1 >= 0 && y - 1 >= 0)
						{
							octupuses[x - 1][y - 1].energyLevel++;
						}
						if (y - 1 >= 0)
						{
							octupuses[x][y - 1].energyLevel++;
						}
						if (x + 1 < nCols && y - 1 >= 0)
						{
							octupuses[x + 1][y - 1].energyLevel++;
						}
						if (x + 1 < nCols)
						{
							octupuses[x + 1][y].energyLevel++;
						}
						if (x + 1 < nCols && y + 1 < nRows)
						{
							octupuses[x + 1][y + 1].energyLevel++;
						}
						if (y + 1 < nRows)
						{
							octupuses[x][y + 1].energyLevel++;
						}
						if (x - 1 >= 0 && y + 1 < nRows)
						{
							octupuses[x - 1][y + 1].energyLevel++;
						}
						if (x - 1 >= 0)
						{
							octupuses[x - 1][y].energyLevel++;
						}

						octupuses[x][y].hasFlashed = 1;
						nTotalFlashes++;
						wasAChange = 1;
					}
				}
			}
		} while (wasAChange);

		for (int y = 0; y < nRows; y++)
		{
			for (int x = 0; x < nCols; x++)
			{
				if (octupuses[x][y].hasFlashed)
				{
					octupuses[x][y].energyLevel = 0;
				}
			}
		}

		printf("After step %d\n", stepCount + 1);
		printEnergyLevels();
	}

	printf("\nAnswer: %d\n", nTotalFlashes);

	fclose(filePointer);
}

void printEnergyLevels()
{
	printf("\n");
	for (int y = 0; y < nRows; y++)
	{
		for (int x = 0; x < nCols; x++)
		{
			if (octupuses[x][y].energyLevel < 10)
			{
				printf("%d", octupuses[x][y].energyLevel);
			}
			else
			{
				printf("0");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void problem2()
{
	char buffer[255];

	FILE *filePointer = fopen("input.txt", "r");

	int y = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		int x = 0;
		while (buffer[x] != '\0')
		{
			octupuses[x][y].energyLevel = buffer[x] - '0';
			x++;
		}
		y++;
		printf("%s\n", buffer);
	}

	int nTotalFlashes = 0;
	int firstStepAllFlash = -1;
	int stepCount = 0;
	while(firstStepAllFlash == -1)
	{
		int nFlashesCurrentStep = 0;

		for (int y = 0; y < nRows; y++)
		{
			for (int x = 0; x < nCols; x++)
			{
				octupuses[x][y].hasFlashed = 0;
				octupuses[x][y].energyLevel++;
			}
		}

		short wasAChange;
		do
		{
			wasAChange = 0;
			for (int y = 0; y < nRows; y++)
			{
				for (int x = 0; x < nCols; x++)
				{
					if (octupuses[x][y].energyLevel > 9 && !octupuses[x][y].hasFlashed)
					{
						if (x - 1 >= 0 && y - 1 >= 0)
						{
							octupuses[x - 1][y - 1].energyLevel++;
						}
						if (y - 1 >= 0)
						{
							octupuses[x][y - 1].energyLevel++;
						}
						if (x + 1 < nCols && y - 1 >= 0)
						{
							octupuses[x + 1][y - 1].energyLevel++;
						}
						if (x + 1 < nCols)
						{
							octupuses[x + 1][y].energyLevel++;
						}
						if (x + 1 < nCols && y + 1 < nRows)
						{
							octupuses[x + 1][y + 1].energyLevel++;
						}
						if (y + 1 < nRows)
						{
							octupuses[x][y + 1].energyLevel++;
						}
						if (x - 1 >= 0 && y + 1 < nRows)
						{
							octupuses[x - 1][y + 1].energyLevel++;
						}
						if (x - 1 >= 0)
						{
							octupuses[x - 1][y].energyLevel++;
						}

						octupuses[x][y].hasFlashed = 1;
						nFlashesCurrentStep++;
						nTotalFlashes++;
						wasAChange = 1;
					}
				}
			}
		} while (wasAChange);

		for (int y = 0; y < nRows; y++)
		{
			for (int x = 0; x < nCols; x++)
			{
				if (octupuses[x][y].hasFlashed)
				{
					octupuses[x][y].energyLevel = 0;
				}
			}
		}

		printf("After step %d\n", stepCount + 1);
		printEnergyLevels();

		if (nFlashesCurrentStep == nRows * nCols)
		{
			firstStepAllFlash = stepCount;
			break;
		}

		stepCount++;
	}

	printf("\nAnswer: %d\n", firstStepAllFlash + 1);

	fclose(filePointer);
}

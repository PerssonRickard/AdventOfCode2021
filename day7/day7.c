#include <stdio.h>
#include <string.h>

void problem1();
void problem2();

int crabPositions[3000];

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char buffer[5000];

	FILE *filePointer = fopen("input.txt", "r");

	if (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);
	}
	else
	{
		printf("Error!\n");
	}

	// Load the initial fish
	int currentCrab;
	char currentChar = -1;
	int i = 0;
	int nCrabs = 0;
	while (currentChar != '\0')
	{
		char smallBuffer[20] = { 0 };
		int j = 0;
		currentChar = -1;
		while (currentChar != ',' && currentChar != '\0')
		{
			currentChar = buffer[i];
			i++;

			smallBuffer[j] = currentChar;
			j++;
		}

		sscanf(smallBuffer, "%d", &currentCrab);
		crabPositions[nCrabs] = currentCrab;
		nCrabs++;
	}

	int minPos = crabPositions[0];
	int maxPos = 0;
	for (i = 0; i < nCrabs; i++)
	{
		if (crabPositions[i] < minPos)
		{
			minPos = crabPositions[i];
		}

		if (crabPositions[i] > maxPos)
		{
			maxPos = crabPositions[i];
		}
	}

	int cheapestAlignPos = -1;
	int cheapestFuelCost = nCrabs*(maxPos - minPos);
	for (int alignPos = minPos; alignPos < maxPos; alignPos++)
	{
		int fuelCost = 0;
		for (i = 0; i < nCrabs; i++)
		{
			if (crabPositions[i] > alignPos)
			{
				fuelCost += crabPositions[i] - alignPos;
			}
			else
			{
				fuelCost += alignPos - crabPositions[i];
			}
		}

		if (fuelCost < cheapestFuelCost)
		{
			cheapestFuelCost = fuelCost;
			cheapestAlignPos = alignPos;
		}
	}

	printf("\nAnswer: Cheapest align position %d. Costs %d fuel\n", cheapestAlignPos, cheapestFuelCost);

	fclose(filePointer);
}

void problem2()
{
	char buffer[5000];

	FILE *filePointer = fopen("input.txt", "r");

	if (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);
	}
	else
	{
		printf("Error!\n");
	}

	// Load the initial fish
	int currentCrab;
	char currentChar = -1;
	int i = 0;
	int nCrabs = 0;
	while (currentChar != '\0')
	{
		char smallBuffer[20] = { 0 };
		int j = 0;
		currentChar = -1;
		while (currentChar != ',' && currentChar != '\0')
		{
			currentChar = buffer[i];
			i++;

			smallBuffer[j] = currentChar;
			j++;
		}

		sscanf(smallBuffer, "%d", &currentCrab);
		crabPositions[nCrabs] = currentCrab;
		nCrabs++;
	}

	int minPos = crabPositions[0];
	int maxPos = 0;
	for (i = 0; i < nCrabs; i++)
	{
		if (crabPositions[i] < minPos)
		{
			minPos = crabPositions[i];
		}

		if (crabPositions[i] > maxPos)
		{
			maxPos = crabPositions[i];
		}
	}

	int cheapestAlignPos = -1;
	unsigned long cheapestFuelCost = nCrabs * (maxPos - minPos)*(maxPos - minPos + 1) / 2;
	for (int alignPos = minPos; alignPos < maxPos; alignPos++)
	{
		unsigned long fuelCost = 0;
		for (i = 0; i < nCrabs; i++)
		{
			int nSteps;
			if (crabPositions[i] > alignPos)
			{
				nSteps = crabPositions[i] - alignPos;
			}
			else
			{
				nSteps = alignPos - crabPositions[i];
			}
			fuelCost += nSteps * (nSteps + 1) / 2;
		}

		if (fuelCost < cheapestFuelCost)
		{
			cheapestFuelCost = fuelCost;
			cheapestAlignPos = alignPos;
		}
	}

	printf("\nAnswer: Cheapest align position %d. Costs %lu fuel\n", cheapestAlignPos, cheapestFuelCost);

	fclose(filePointer);
}

#include <stdio.h>
#include <string.h>

#define POPULATION_MAX_SIZE 1000000
#define MAX_N_DAYS 8

void problem1();
void problem2();
unsigned char lanternfishPopulation[POPULATION_MAX_SIZE];

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	FILE *filePointer;
	char buffer[1000];

	fopen_s(&filePointer, "input.txt", "r");

	if (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);
	}
	else
	{
		printf("Error!\n");
	}

	// Load the initial fish
	unsigned char currentFish;
	char currentChar = -1;
	int i = 0;
	int nLanternfish = 0;
	while (currentChar != '\0')
	{
		currentChar = buffer[i];
		if (currentChar != ',' && currentChar != '\0')
		{
			currentFish = currentChar - '0';
			lanternfishPopulation[nLanternfish] = currentFish;
			nLanternfish++;
		}
		i++;
	}

	int nLanternFishStartOfDay;
	for (int day = 0; day < 80; day++)
	{
		nLanternFishStartOfDay = nLanternfish;
		for (i = 0; i < nLanternFishStartOfDay; i++)
		{
			if (lanternfishPopulation[i] == 0)
			{
				lanternfishPopulation[i] = 7;
				lanternfishPopulation[nLanternfish] = 8;
				nLanternfish++;

				if (nLanternfish >= POPULATION_MAX_SIZE)
				{
					printf("Error! Number of fishes larger than allocated array!\n");
				}
			}

			lanternfishPopulation[i]--;
		}
	}

	printf("\nAnswer: %d\n", nLanternfish);

	fclose(filePointer);
}

void problem2()
{
	FILE *filePointer;
	char buffer[1000];

	fopen_s(&filePointer, "input.txt", "r");

	if (fscanf(filePointer, "%s", buffer) == 1)
	{
		printf("%s\n", buffer);
	}
	else
	{
		printf("Error!\n");
	}

	// Load the initial fish
	unsigned char currentFish;
	char currentChar = -1;
	int i = 0;
	unsigned long long nLanternfish = 0;
	long long nFishForEachNRemainingDays[9] = { 0 };
	while (currentChar != '\0')
	{
		currentChar = buffer[i];
		if (currentChar != ',' && currentChar != '\0')
		{
			currentFish = currentChar - '0';
			nFishForEachNRemainingDays[currentFish]++;
		}
		i++;
	}

	//int nLanternFishStartOfDay;
	long long temp1, temp2 = 0;
	for (int day = 0; day < 256; day++)
	{
		// Shift nFishForEachNRemainingDays to the left to decrease
		// the number of days by 1
		temp1 = nFishForEachNRemainingDays[MAX_N_DAYS];
		for (i = MAX_N_DAYS; i > 0; i--)
		{
			if (i % 2 == 0)
			{
				temp2 = nFishForEachNRemainingDays[i - 1];
				nFishForEachNRemainingDays[i - 1] = temp1;
			}
			else
			{
				temp1 = nFishForEachNRemainingDays[i - 1];
				nFishForEachNRemainingDays[i - 1] = temp2;
			}

		}

		// temp1 will hold the number of fish which were previously at day 0
		nFishForEachNRemainingDays[6] += temp1;
		nFishForEachNRemainingDays[8] = temp1;
	}

	for (int i = 0; i < MAX_N_DAYS + 1; i++)
	{
		nLanternfish += nFishForEachNRemainingDays[i];
	}

	printf("\nAnswer: %llu\n", nLanternfish);

	fclose(filePointer);
}
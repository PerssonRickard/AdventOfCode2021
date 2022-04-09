
#include <stdio.h>
#include <string.h>

#define nBits 12

void problem1();
void problem2();

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	FILE *filePointer;
	char stringInput[255];
	signed int bitVote[nBits] = { 0 };

	int bit = 0;
	int i;

	fopen_s(&filePointer, "input.txt", "r");

	while (fscanf(filePointer, "%s", stringInput) == 1)
	{
		for (i = 0; i < nBits; i++)
		{
			bit = stringInput[i] - '0';

			if (bit == 1)
			{
				bitVote[i] += 1;
			}
			else
			{
				bitVote[i] -= 1;
			}
		}
	}


	int gamma = 0;
	int epsilon = 0;
	int powerOfTwo = 1;
	for (i = nBits - 1; i >= 0; i--)
	{
		if (bitVote[i] > 0)
		{
			gamma += powerOfTwo;
			powerOfTwo = powerOfTwo * 2;
		}
		else if (bitVote[i] < 0)
		{
			epsilon += powerOfTwo;
			powerOfTwo = powerOfTwo * 2;
		}
		else
		{
			printf("Error!\n");
		}
	}

	printf("\n\n\nAnswer: %d (gamma) * %d (epsilon) = %d\n", gamma, epsilon, gamma*epsilon);

	fclose(filePointer);
}

void problem2()
{
	FILE *filePointer;
	char stringInput[255];
	char input[1000][nBits];

	int bit = 0;
	int i = 0;

	fopen_s(&filePointer, "input.txt", "r");

	while (fscanf(filePointer, "%s", stringInput) == 1) // load the data once
	{
		strncpy(input[i], stringInput, nBits);
		i++;
	}

	int oxygen = filterNumbers(input, 1);
	int carbonDioxide = filterNumbers(input, 0);

	printf("\n\n\nAnswer: %d (oxygen) * %d (carbonDioxide) = %d\n", oxygen, carbonDioxide, oxygen*carbonDioxide);

	fclose(filePointer);
}

int filterNumbers(char input[1000][nBits], int keepMostCommon)
{
	int bit = 0;
	int i;
	int index;

	int indicesWithOneBit[1000] = { 0 };
	int indicesWithZeroBit[1000] = { 0 };
	for (i = 0; i < 1000; i++)
	{
		indicesWithOneBit[i] = i;
	}
	int numbersWithOneBitSize = 0;
	int numbersWithZeroBitSize = 0;

	int* currentIndices;
	currentIndices = indicesWithOneBit;
	int currentNumbersSize = 1000;

	int bitPos = 0;
	while (currentNumbersSize > 1 && bitPos < nBits)
	{
		for (i = 0; i < currentNumbersSize; i++)
		{
			index = currentIndices[i];
			bit = input[index][bitPos] - '0';

			if (bit == 1)
			{
				indicesWithOneBit[numbersWithOneBitSize] = index;
				numbersWithOneBitSize++;
			}
			else if (bit == 0)
			{
				indicesWithZeroBit[numbersWithZeroBitSize] = index;
				numbersWithZeroBitSize++;
			}
			else
			{
				printf("Error!\n");
			}
		}

		if (numbersWithOneBitSize > numbersWithZeroBitSize)
		{
			if (keepMostCommon)
			{
				currentIndices = indicesWithOneBit;
				currentNumbersSize = numbersWithOneBitSize;
			}
			else
			{
				currentIndices = indicesWithZeroBit;
				currentNumbersSize = numbersWithZeroBitSize;
			}
		}
		else if (numbersWithOneBitSize < numbersWithZeroBitSize)
		{
			if (keepMostCommon)
			{
				currentIndices = indicesWithZeroBit;
				currentNumbersSize = numbersWithZeroBitSize;;
			}
			else
			{
				currentIndices = indicesWithOneBit;
				currentNumbersSize = numbersWithOneBitSize;
			}
		}
		else
		{
			if (keepMostCommon)
			{
				currentIndices = indicesWithOneBit;
				currentNumbersSize = numbersWithOneBitSize;
			}
			else
			{
				currentIndices = indicesWithZeroBit;
				currentNumbersSize = numbersWithZeroBitSize;
			}
		}
		numbersWithOneBitSize = 0;
		numbersWithZeroBitSize = 0;
		bitPos++;
	}
	
	int finalIndex = currentIndices[0];
	
	int result = 0;
	int powerOfTwo = 1;
	for (i = nBits - 1; i >= 0; i--)
	{
		bit = input[finalIndex][i] - '0';
		result += bit * powerOfTwo;
		powerOfTwo = powerOfTwo * 2;
	}

	return result;
}
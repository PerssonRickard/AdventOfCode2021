#include <stdio.h>
#include <string.h>

void problem1();
void problem2();

typedef struct segmentToWireMappingS
{
	char a;
	char b;
	char c;
	char d;
	char e;
	char f;
	char g;
} segmentToWireMappingS;

typedef struct signalPatternS
{
	char pattern[7];
	unsigned short patternLength;
	unsigned short digit;
	short digitFound;
} signalPatternS;

short decodePatternToDigit(char pattern[7], segmentToWireMappingS* segmentToWireMapping_p);

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char buffer[255];

	FILE *filePointer = fopen("input.txt", "r");

	int digitCount = 0;
	while (fgets(buffer, 255, filePointer))
	{
		int i = 0;
		while (buffer[i] != '|' && i < 255)
		{
			i++;
		}
		i++;

		for (int j = 0; j < 4; j++)
		{
			i++;

			int segmentCount = 0;
			while (buffer[i] != ' ' && buffer[i] != '\n')
			{
				segmentCount++;
				i++;
			}

			if (segmentCount == 2 || segmentCount == 4 || segmentCount == 3 || segmentCount == 7)
			{
				digitCount++;
			}
		}
	}

	printf("\nAnswer: %d\n", digitCount);

	fclose(filePointer);
}

void problem2()
{

	signalPatternS input[200][14] = {};
	char buffer[255];

	FILE *filePointer = fopen("input.txt", "r");

	// Store input
	int i = 0, j = 0, k = 0, w = 0;
	while (fgets(buffer, 255, filePointer))
	{
		i = 0;
		k = 0;
		while (buffer[i] != '\n' && i < 255)
		{
			while (buffer[i] == ' ' || buffer[i] == '|')
			{
				i++;
			}

			w = 0;
			while (buffer[i] != ' ' && buffer[i] != '\n')
			{
				input[j][k].pattern[w] = buffer[i];
				i++;
				w++;
			}
			input[j][k].patternLength = w;
			if (w == 2)
			{
				input[j][k].digit = 1;
				input[j][k].digitFound = 1;
			}
			if (w == 3)
			{
				input[j][k].digit = 7;
				input[j][k].digitFound = 1;
			}
			if (w == 4)
			{
				input[j][k].digit = 4;
				input[j][k].digitFound = 1;
			}
			if (w == 7)
			{
				input[j][k].digit = 8;
				input[j][k].digitFound = 1;
			}
			k++;
		}
		j++;
	}

	segmentToWireMappingS segmentToWireMapping = { 0 };
	int sum = 0;
	char currentChar;
	for (i = 0; i < 200; i++)
	{
		short digitToPatternIndex[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		signalPatternS currentSignalPatterns[14];
		for (j = 0; j < 14; j++)
		{
			currentSignalPatterns[j] = input[i][j];

			if (j < 10)
			{
				if (currentSignalPatterns[j].digitFound)
				{
					digitToPatternIndex[currentSignalPatterns[j].digit] = j;
				}
			}
		}



		// Compare 7 to 1, the wire that 1 does not have is segment a
		for (int k = 0; k < 3; k++)
		{
			currentChar = currentSignalPatterns[digitToPatternIndex[7]].pattern[k];
			if (currentChar != currentSignalPatterns[digitToPatternIndex[1]].pattern[0] &&
				currentChar != currentSignalPatterns[digitToPatternIndex[1]].pattern[1])
			{
				segmentToWireMapping.a = currentChar;
				break;
			}
		}

		// Compare 4 to all unknown numbers, the one with all wires same as (4 + wire to segment a) + 1 extra wire
		// is 9 and the extra wire is to segment g
		for (j = 0; j < 10; j++)
		{
			if (j == digitToPatternIndex[1] || j == digitToPatternIndex[7] || j == digitToPatternIndex[4] || j == digitToPatternIndex[8])
			{
				continue;
			}

			int k = 0;
			int sameCount = 0;
			currentChar = -1;
			char extraWire = -1;
			while (currentChar != '\0')
			{
				currentChar = currentSignalPatterns[j].pattern[k];
				if (currentChar == currentSignalPatterns[digitToPatternIndex[4]].pattern[0] || 
					currentChar == currentSignalPatterns[digitToPatternIndex[4]].pattern[1] ||
					currentChar == currentSignalPatterns[digitToPatternIndex[4]].pattern[2] ||
					currentChar == currentSignalPatterns[digitToPatternIndex[4]].pattern[3] ||
					currentChar == segmentToWireMapping.a)
				{
					sameCount++;
				}
				else if (currentChar != '\0')
				{
					extraWire = currentChar;
				}
				k++;
			}
			if (sameCount == 5 && currentSignalPatterns[j].patternLength == 6)
			{
				currentSignalPatterns[j].digit = 9;
				currentSignalPatterns[j].digitFound = 1;
				digitToPatternIndex[9] = j;
				segmentToWireMapping.g = extraWire;
				break;
			}
		}
		
		// The wire that 9 is missing goes to segment e
		char allWires[7] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
		for (j = 0; j < 7; j++)
		{
			short isMissing = 1;
			for (k = 0; k < 6; k++)
			{
				if (allWires[j] == currentSignalPatterns[digitToPatternIndex[9]].pattern[k])
				{
					isMissing = 0;
					break;
				}
			}
			if (isMissing)
			{
				segmentToWireMapping.e = allWires[j];
			}
		}

		// Compare (e, g, a and 1) to all unknown numbers, the number with all wires the same + 1 extra wire
		// is 0 and the extra wire is to segment b
		for (j = 0; j < 10; j++)
		{
			if (j == digitToPatternIndex[1] || j == digitToPatternIndex[7] || j == digitToPatternIndex[4] || j == digitToPatternIndex[8] ||
				j == digitToPatternIndex[9])
			{
				continue;
			}

			int k = 0;
			int sameCount = 0;
			currentChar = -1;
			char extraWire = -1;
			while (currentChar != '\0')
			{
				currentChar = currentSignalPatterns[j].pattern[k];
				if (currentChar == currentSignalPatterns[digitToPatternIndex[1]].pattern[0] ||
					currentChar == currentSignalPatterns[digitToPatternIndex[1]].pattern[1] ||
					currentChar == segmentToWireMapping.e ||
					currentChar == segmentToWireMapping.g ||
					currentChar == segmentToWireMapping.a)
				{
					sameCount++;
				}
				else if (currentChar != '\0')
				{
					extraWire = currentChar;
				}
				k++;
			}
			if (sameCount == 5 && currentSignalPatterns[j].patternLength == 6)
			{
				currentSignalPatterns[j].digit = 0;
				currentSignalPatterns[j].digitFound = 1;
				digitToPatternIndex[0] = j;
				segmentToWireMapping.b = extraWire;
				break;
			}
		}

		// The wire that 0 is missing goes to segment d
		for (j = 0; j < 7; j++)
		{
			short isMissing = 1;
			for (k = 0; k < 6; k++)
			{
				if (allWires[j] == currentSignalPatterns[digitToPatternIndex[0]].pattern[k])
				{
					isMissing = 0;
					break;
				}
			}
			if (isMissing)
			{
				segmentToWireMapping.d = allWires[j];
			}
		}

		// Compare (a, b, d, and g) to all unknown numbers, the number with all wires the same + 1 extra wire
		// is 5 and the extra wire is to segment f
		for (j = 0; j < 10; j++)
		{
			if (j == digitToPatternIndex[1] || j == digitToPatternIndex[7] || j == digitToPatternIndex[4] || j == digitToPatternIndex[8] ||
				j == digitToPatternIndex[9] || j == digitToPatternIndex[0])
			{
				continue;
			}

			int k = 0;
			int sameCount = 0;
			currentChar = -1;
			char extraWire = -1;
			while (currentChar != '\0')
			{
				currentChar = currentSignalPatterns[j].pattern[k];
				if (currentChar == segmentToWireMapping.a ||
					currentChar == segmentToWireMapping.b ||
					currentChar == segmentToWireMapping.d ||
					currentChar == segmentToWireMapping.g)
				{
					sameCount++;
				}
				else if (currentChar != '\0')
				{
					extraWire = currentChar;
				}
				k++;
			}
			if (sameCount == 4 && currentSignalPatterns[j].patternLength == 5)
			{
				currentSignalPatterns[j].digit = 5;
				currentSignalPatterns[j].digitFound = 1;
				digitToPatternIndex[5] = j;
				segmentToWireMapping.f = extraWire;
				break;
			}
		}

		// The last missing wire is to segment c
		for (j = 0; j < 7; j++)
		{
			currentChar = allWires[j];
			if (currentChar != segmentToWireMapping.a &&
				currentChar != segmentToWireMapping.b &&
				currentChar != segmentToWireMapping.d &&
				currentChar != segmentToWireMapping.e &&
				currentChar != segmentToWireMapping.f &&
				currentChar != segmentToWireMapping.g)
			{
				segmentToWireMapping.c = currentChar;
				break;
			}
		}

		short digit;
		int powerOfTen = 1000;
		int number = 0;
		for (j = 10; j < 14; j++)
		{
			digit = decodePatternToDigit(currentSignalPatterns[j].pattern, &segmentToWireMapping);
			number += powerOfTen * digit;
			powerOfTen = powerOfTen / 10;
		}

		sum += number;
	}


	printf("\nAnswer: %d\n", sum);

	fclose(filePointer);
}

short decodePatternToDigit(char pattern[7], segmentToWireMappingS* segmentToWireMapping_p)
{
	short digit = -1;
	short isSegmentOn[7] = {0};
	
	int i = 0;
	char currentChar = pattern[i];
	while (currentChar != '\0' && i < 7)
	{
		if (currentChar == segmentToWireMapping_p->a)
		{
			isSegmentOn[0] = 1;
		}
		else if (currentChar == segmentToWireMapping_p->b)
		{
			isSegmentOn[1] = 1;
		}
		else if (currentChar == segmentToWireMapping_p->c)
		{
			isSegmentOn[2] = 1;
		}
		else if (currentChar == segmentToWireMapping_p->d)
		{
			isSegmentOn[3] = 1;
		}
		else if (currentChar == segmentToWireMapping_p->e)
		{
			isSegmentOn[4] = 1;
		}
		else if (currentChar == segmentToWireMapping_p->f)
		{
			isSegmentOn[5] = 1;
		}
		else if (currentChar == segmentToWireMapping_p->g)
		{
			isSegmentOn[6] = 1;
		}

		i++;
		currentChar = pattern[i];
	}

	if (isSegmentOn[0] && isSegmentOn[1] && isSegmentOn[2] && !isSegmentOn[3] &&
		isSegmentOn[4] && isSegmentOn[5] && isSegmentOn[6])
	{
		digit = 0;
	}
	else if (!isSegmentOn[0] && !isSegmentOn[1] && isSegmentOn[2] && !isSegmentOn[3] && 
			 !isSegmentOn[4] && isSegmentOn[5] && !isSegmentOn[6])
	{
		digit = 1;
	}
	else if (isSegmentOn[0] && !isSegmentOn[1] && isSegmentOn[2] && isSegmentOn[3] &&
		isSegmentOn[4] && !isSegmentOn[5] && isSegmentOn[6])
	{
		digit = 2;
	}
	else if (isSegmentOn[0] && !isSegmentOn[1] && isSegmentOn[2] && isSegmentOn[3] &&
		!isSegmentOn[4] && isSegmentOn[5] && isSegmentOn[6])
	{
		digit = 3;
	}
	else if (!isSegmentOn[0] && isSegmentOn[1] && isSegmentOn[2] && isSegmentOn[3] &&
		!isSegmentOn[4] && isSegmentOn[5] && !isSegmentOn[6])
	{
		digit = 4;
	}
	else if (isSegmentOn[0] && isSegmentOn[1] && !isSegmentOn[2] && isSegmentOn[3] &&
		!isSegmentOn[4] && isSegmentOn[5] && isSegmentOn[6])
	{
		digit = 5;
	}
	else if (isSegmentOn[0] && isSegmentOn[1] && !isSegmentOn[2] && isSegmentOn[3] &&
		isSegmentOn[4] && isSegmentOn[5] && isSegmentOn[6])
	{
		digit = 6;
	}
	else if (isSegmentOn[0] && !isSegmentOn[1] && isSegmentOn[2] && !isSegmentOn[3] &&
		!isSegmentOn[4] && isSegmentOn[5] && !isSegmentOn[6])
	{
		digit = 7;
	}
	else if (isSegmentOn[0] && isSegmentOn[1] && isSegmentOn[2] && isSegmentOn[3] &&
		isSegmentOn[4] && isSegmentOn[5] && isSegmentOn[6])
	{
		digit = 8;
	}
	else if (isSegmentOn[0] && isSegmentOn[1] && isSegmentOn[2] && isSegmentOn[3] &&
		!isSegmentOn[4] && isSegmentOn[5] && isSegmentOn[6])
	{
		digit = 9;
	}
	else
	{
		printf("Error, no digit matches!\n");
	}

	return digit;
}

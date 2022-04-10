#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define POLYMER_MAX_SIZE 100000
#define MAX_N_INSERTION_RULES 200
#define MAX_N_UNIQUE_ELEMENTS 50
#define MAX_N_UNIQUE_PAIRS 150

void problem1();
void problem2();
void addUniqueElement(char element);
void addUniquePair(char pair[3]);

typedef struct insertionRuleS
{
	char pair[3];
	char insertion[2];
} insertionRuleS;

insertionRuleS insertionRules[MAX_N_INSERTION_RULES];
int nInsertionRules = 0;
char polymer1[POLYMER_MAX_SIZE] = { 0 };
char polymer2[POLYMER_MAX_SIZE] = { 0 };
char uniqueElements[MAX_N_UNIQUE_ELEMENTS] = { 0 };
char uniquePairs[MAX_N_UNIQUE_PAIRS][2] = { 0 };
int nUniqueElements = 0;
int nUniquePairs = 0;
unsigned long long pairQuantities[MAX_N_UNIQUE_PAIRS] = { 0 };

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char buffer[255];
	char pair[3];
	char insertion[2];

	FILE *filePointer = fopen("input.txt", "r");

	// Read template
	fscanf(filePointer, "%s", buffer);
	printf("%s\n", buffer);
	int polymerSize = 0;
	while (buffer[polymerSize] != 0)
	{
		polymer1[polymerSize] = buffer[polymerSize];
		polymerSize++;

		addUniqueElement(buffer[polymerSize]);
	}

	// Read the pair insertion rules
	int i = 0;
	while (fscanf(filePointer, "%s -> %s", pair, insertion) == 2)
	{
		printf("%s -> %s\n", pair, insertion);

		insertionRules[i].pair[0] = pair[0];
		insertionRules[i].pair[1] = pair[1];
		insertionRules[i].insertion[0] = insertion[0];
		nInsertionRules++;

		addUniqueElement(pair[0]);
		addUniqueElement(pair[1]);
		addUniqueElement(insertion[0]);

		i++;
	}

	char* polymer = polymer1;
	char* newPolymer = polymer2;
	int nSteps = 10;
	for (i = 0; i < nSteps; i++)
	{
		int newPolymerSize = 0;
		for (int j = 0; j < polymerSize; j++)//while (polymer[j+1] != 0) // use polymerSize instead
		{
			pair[0] = polymer[j];
			pair[1] = polymer[j+1];
			bool ruleApplied = false;
			
			for (int iRule = 0; iRule < nInsertionRules; iRule++)
			{
				if (insertionRules[iRule].pair[0] == pair[0] && insertionRules[iRule].pair[1] == pair[1])
				{
					newPolymer[newPolymerSize] = pair[0];
					newPolymer[newPolymerSize + 1] = insertionRules[iRule].insertion[0];
					//newPolymer[newPolymerSize + 2] = pair[1];
					newPolymerSize += 2;
					ruleApplied = true;
					break;
				}
			}

			if (!ruleApplied)
			{
				newPolymer[newPolymerSize] = pair[0];
				//newPolymer[newPolymerSize + 1] = pair[1];
				newPolymerSize++;
			}
		}

		char* temp = polymer;
		polymer = newPolymer;
		newPolymer = temp;
		polymerSize = newPolymerSize;
	}

	int elementQuantities[MAX_N_UNIQUE_ELEMENTS] = { 0 };
	for (i = 0; i < polymerSize; i++)
	{
		for (int j = 0; j < nUniqueElements; j++)
		{
			if (polymer[i] == uniqueElements[j])
			{
				elementQuantities[j]++;
				break;
			}
		}
	}

	int minQuantity = elementQuantities[0];
	int maxQuantity = 0;
	for (i = 0; i < nUniqueElements; i++)
	{
		if (elementQuantities[i] < minQuantity)
		{
			minQuantity = elementQuantities[i];
		}
		if (elementQuantities[i] > maxQuantity)
		{
			maxQuantity = elementQuantities[i];
		}
	}

	printf("\nAnswer: %d (most common) - %d (least common) = %d \n", maxQuantity, minQuantity, maxQuantity - minQuantity);

	fclose(filePointer);
}

void addUniqueElement(char element)
{
	if (element == 0)
	{
		return;
	}

	int i = 0;
	bool alreadyAdded = false;
	while (uniqueElements[i] != 0)
	{
		if (uniqueElements[i] == element)
		{
			alreadyAdded = true;
			break;
		}
		i++;
	}

	if (!alreadyAdded)
	{
		uniqueElements[i] = element;
		nUniqueElements++;
	}
}

void problem2()
{
	char buffer[255];
	char pair[3];
	char insertion[2];
	char lastElement = 0;

	FILE *filePointer = fopen("input.txt", "r");

	// Read template
	fscanf(filePointer, "%s", buffer);
	printf("%s\n", buffer);
	int polymerSize = 0;
	while (buffer[polymerSize] != 0)
	{
		polymer1[polymerSize] = buffer[polymerSize];
		polymerSize++;

		addUniqueElement(buffer[polymerSize]);
	}
	lastElement = buffer[polymerSize - 1];

	// Read the pair insertion rules
	int i = 0;
	while (fscanf(filePointer, "%s -> %s", pair, insertion) == 2)
	{
		printf("%s -> %s\n", pair, insertion);

		insertionRules[i].pair[0] = pair[0];
		insertionRules[i].pair[1] = pair[1];
		insertionRules[i].insertion[0] = insertion[0];
		nInsertionRules++;

		addUniqueElement(pair[0]);
		addUniqueElement(pair[1]);
		addUniqueElement(insertion[0]);

		i++;
	}

	for (i = 0; i < nUniqueElements; i++)
	{
		for (int j = 0; j < nUniqueElements; j++)
		{
			pair[0] = uniqueElements[i];
			pair[1] = uniqueElements[j];
			addUniquePair(pair);
		}
	}

	for (i = 0; i < polymerSize - 1; i++)
	{
		pair[0] = polymer1[i];
		pair[1] = polymer1[i + 1];
		
		for (int iPair = 0; iPair < nUniquePairs; iPair++)
		{
			if (uniquePairs[iPair][0] == pair[0] && uniquePairs[iPair][1] == pair[1])
			{
				pairQuantities[iPair]++;
			}
		}
	}


	int nSteps = 40;
	char leftPair[3] = { 0 };
	char rightPair[3] = { 0 };
	for (i = 0; i < nSteps; i++)
	{
		unsigned long long newPairQuantities[MAX_N_UNIQUE_PAIRS] = { 0 };
		for (int iPair = 0; iPair < nUniquePairs; iPair++)
		{
			if (pairQuantities[iPair] == 0)
			{
				continue;
			}

			pair[0] = uniquePairs[iPair][0];
			pair[1] = uniquePairs[iPair][1];

			bool ruleApplied = false;
			for (int iRule = 0; iRule < nInsertionRules; iRule++)
			{
				if (insertionRules[iRule].pair[0] == pair[0] && insertionRules[iRule].pair[1] == pair[1])
				{
					ruleApplied = true;

					leftPair[0] = pair[0];
					leftPair[1] = insertionRules[iRule].insertion[0];
					rightPair[0] = insertionRules[iRule].insertion[0];
					rightPair[1] = pair[1];

					bool leftPairFound = false;
					bool rightPairFound = false;
					for (int jPair = 0; jPair < nUniquePairs; jPair++)
					{
						if (uniquePairs[jPair][0] == leftPair[0] && uniquePairs[jPair][1] == leftPair[1])
						{
							newPairQuantities[jPair] += pairQuantities[iPair];
							leftPairFound = true;
						}
						if (uniquePairs[jPair][0] == rightPair[0] && uniquePairs[jPair][1] == rightPair[1])
						{
							newPairQuantities[jPair] += pairQuantities[iPair];
							rightPairFound = true;
						}

						if (leftPairFound && rightPairFound)
						{
							break;
						}
					}
				}
				if (ruleApplied)
				{
					break;
				}
			}
		}

		// Copy over from the local array newPairQuantities
		for (int iPair = 0; iPair < nUniquePairs; iPair++)
		{
			pairQuantities[iPair] = newPairQuantities[iPair];
		}
	}
	

	unsigned long long elementQuantities[MAX_N_UNIQUE_ELEMENTS] = { 0 };
	for (int iPair = 0; iPair < nUniquePairs; iPair++)
	{
		for (int iElement = 0; iElement < 1; iElement++) // Only count the first element as to not add
		{												 // an element in an overlapping pair twice
			for (int j = 0; j < nUniqueElements; j++)
			{
				if (uniquePairs[iPair][iElement] == uniqueElements[j])
				{
					elementQuantities[j] += pairQuantities[iPair];
					break;
				}
			}
		}
	}

	// Add 1 count to the element which started in the last place since it 
	// will always be in the last place and was not counted in the pairs
	for (i = 0; i < nUniqueElements; i++)
	{
		if (uniqueElements[i] == lastElement)
		{
			elementQuantities[i]++;
		}
	}

	unsigned long long minQuantity = elementQuantities[0];
	unsigned long long maxQuantity = 0;
	for (i = 0; i < nUniqueElements; i++)
	{
		if (elementQuantities[i] < minQuantity)
		{
			minQuantity = elementQuantities[i];
		}
		if (elementQuantities[i] > maxQuantity)
		{
			maxQuantity = elementQuantities[i];
		}
	}

	printf("\nAnswer: %llu (most common) - %llu (least common) = %llu \n", maxQuantity, minQuantity, maxQuantity - minQuantity);

	fclose(filePointer);
}


void addUniquePair(char pair[3])
{
	if (pair[0] == 0 || pair[1] == 0)
	{
		return;
	}

	int i = 0;
	bool alreadyAdded = false;
	while (uniquePairs[i][0] != 0 && uniquePairs[i][1] != 0)
	{
		if (uniquePairs[i][0] == pair[0] && uniquePairs[i][1] == pair[1])
		{
			alreadyAdded = true;
			break;
		}
		i++;
	}

	if (!alreadyAdded)
	{
		uniquePairs[i][0] = pair[0];
		uniquePairs[i][1] = pair[1];
		nUniquePairs++;
	}
}

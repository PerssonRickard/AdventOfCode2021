#include <stdio.h>
#include <string.h>

void problem1();
void problem2();

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char buffer[255];
	char expectedClosingCharacter[255] = { 0 };

	FILE *filePointer = fopen("input.txt", "r");

	int syntaxErrorScore = 0;
	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		int i = 0;
		int j = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '(')
			{
				expectedClosingCharacter[j] = ')';
				j++;
			}
			else if (buffer[i] == '[')
			{
				expectedClosingCharacter[j] = ']';
				j++;
			}
			else if (buffer[i] == '{')
			{
				expectedClosingCharacter[j] = '}';
				j++;
			}
			else if (buffer[i] == '<')
			{
				expectedClosingCharacter[j] = '>';
				j++;
			}
			else
			{
				// Does not account for the first character on the line being a closing character
				// but that doesn't seem to be a possible input for this problem
				j--;
				if (buffer[i] != expectedClosingCharacter[j])
				{
					// First incorrect closing character found

					if (buffer[i] == ')')
					{
						syntaxErrorScore += 3;
					}
					else if (buffer[i] == ']')
					{
						syntaxErrorScore += 57;
					}
					else if (buffer[i] == '}')
					{
						syntaxErrorScore += 1197;
					}
					else if (buffer[i] == '>')
					{
						syntaxErrorScore += 25137;
					}
					break;
				}
			}

			i++;
		}
		printf("%s\n", buffer);
	}

	printf("\nAnswer: %d\n", syntaxErrorScore);

	fclose(filePointer);
}

void problem2()
{
	char buffer[255];
	char expectedClosingCharacter[255] = { 0 };
	unsigned long long completionStringScores[255] = { 0 };
	int nCompletionStrings = 0;

	FILE *filePointer = fopen("input.txt", "r");

	while (fscanf(filePointer, "%s", buffer) == 1)
	{
		int i = 0;
		int j = 0;
		short corruptedLine = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '(')
			{
				expectedClosingCharacter[j] = ')';
				j++;
			}
			else if (buffer[i] == '[')
			{
				expectedClosingCharacter[j] = ']';
				j++;
			}
			else if (buffer[i] == '{')
			{
				expectedClosingCharacter[j] = '}';
				j++;
			}
			else if (buffer[i] == '<')
			{
				expectedClosingCharacter[j] = '>';
				j++;
			}
			else
			{
				// Does not account for the first character on the line being a closing character
				// but that doesn't seem to be a possible input for this problem
				j--;
				if (buffer[i] != expectedClosingCharacter[j])
				{
					// First incorrect closing character found
					// Corrputed line, discard it!
					corruptedLine = 1;
					break;
				}
			}

			i++;
		}

		if (!corruptedLine)
		{
			// The whole line has been iterated over and it was not identified as a corrupt line.
			// The array expectedClosingCharacter now holds the missing closing characters
			// in reverse order with an array size of j.
			for (int k = j-1; k >= 0; k--)
			{
				completionStringScores[nCompletionStrings] = completionStringScores[nCompletionStrings] * 5;
				if (expectedClosingCharacter[k] == ')')
				{
					completionStringScores[nCompletionStrings] += 1;
				}
				else if (expectedClosingCharacter[k] == ']')
				{
					completionStringScores[nCompletionStrings] += 2;
				}
				else if (expectedClosingCharacter[k] == '}')
				{
					completionStringScores[nCompletionStrings] += 3;
				}
				else if (expectedClosingCharacter[k] == '>')
				{
					completionStringScores[nCompletionStrings] += 4;
				}
			}
			nCompletionStrings++;
		}
		
		printf("%s\n", buffer);
	}

	// Sort the scores
	int nUnsortedScores = nCompletionStrings;
	unsigned long long temp;
	while (nUnsortedScores != 0)
	{
		for (int i = 0; i < nUnsortedScores - 1; i++)
		{
			temp = completionStringScores[i];
			if (temp > completionStringScores[i + 1])
			{
				completionStringScores[i] = completionStringScores[i + 1];
				completionStringScores[i + 1] = temp;
			}
		}
		nUnsortedScores--;
	}

	unsigned long long middleScore = completionStringScores[(nCompletionStrings - 1) / 2];

	printf("\nAnswer: %llu\n", middleScore);

	fclose(filePointer);
}

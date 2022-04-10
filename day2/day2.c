
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
	char stringInput[255];
	int intInput;

	int horizontalPos = 0;
	int depth = 0;

	FILE *filePointer = fopen("input.txt", "r");

	while (fscanf(filePointer, "%s %d", stringInput, &intInput)==2)
	{

		if (!strcmp("forward", stringInput))
		{
			horizontalPos += intInput;
		}
		else if (!strcmp("down", stringInput))
		{
			depth += intInput;
		}
		else if (!strcmp("up", stringInput))
		{
			depth -= intInput;
		}
		else
		{
			printf("Error!\n");
		}
	}

	printf("\n\n\nAnswer: %d (horizontal position) * %d (depth) = %d\n", horizontalPos, depth, horizontalPos*depth);

	fclose(filePointer);
}

void problem2()
{
	char stringInput[255];
	int intInput;

	int horizontalPos = 0;
	int depth = 0;
	int aim = 0;

	FILE *filePointer = fopen("input.txt", "r");

	while (fscanf(filePointer, "%s %d", stringInput, &intInput) == 2)
	{

		if (!strcmp("forward", stringInput))
		{
			horizontalPos += intInput;
			depth += aim * intInput;
		}
		else if (!strcmp("down", stringInput))
		{
			aim += intInput;
		}
		else if (!strcmp("up", stringInput))
		{
			aim -= intInput;
		}
		else
		{
			printf("Error!\n");
		}
	}

	printf("\n\n\nAnswer: %d (horizontal position) * %d (depth) = %d\n", horizontalPos, depth, horizontalPos*depth);

	fclose(filePointer);
}

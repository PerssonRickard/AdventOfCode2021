
#include <stdio.h>

void problem1();
void problem2();

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char buff[255];

	FILE *fp = fopen("input.txt", "r");


	int currentDepth;
	int prevDepth = -1;
	int increasingMeasCount = 0;

	while (fgets(buff, 255, (FILE*)fp))
	{
		sscanf(buff, "%d", &currentDepth);

		if (prevDepth != -1)
		{
			if (currentDepth > prevDepth)
			{
				increasingMeasCount++;
			}
		}
		prevDepth = currentDepth;

	}

	printf("Answer: %d\n", increasingMeasCount);

	fclose(fp);
}

void problem2()
{
	char buff[255];
	int slidingWindow[3];
	int windowSize = 0;
	int i = 0;

	FILE *fp = fopen("input.txt", "r");


	int currentDepth;
	int currentSum = -1;
	int prevSum = -1;
	int increasingMeasCount = 0;

	while (fgets(buff, 255, (FILE*)fp))
	{
		sscanf(buff, "%d", &currentDepth);

		slidingWindow[i] = currentDepth;
		i = (i + 1) % 3;

		if (windowSize < 3)
		{
			windowSize++;
		}

		if (windowSize == 3)
		{
			currentSum = slidingWindow[0] + slidingWindow[1] + slidingWindow[2];
		}

		if (prevSum != -1)
		{
			if (currentSum > prevSum)
			{
				increasingMeasCount++;
			}
		}

		if (currentSum != -1)
		{
			prevSum = currentSum;
		}

	}

	printf("Answer: %d\n", increasingMeasCount);

	fclose(fp);
}

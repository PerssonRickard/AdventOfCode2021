
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
	FILE *fp;
	char buff[255];

	fopen_s(&fp, "input.txt", "r");


	int currentDepth;
	int prevDepth = NULL;
	int increasingMeasCount = 0;

	while (fgets(buff, 255, (FILE*)fp))
	{
		sscanf_s(buff, "%d", &currentDepth);

		if (prevDepth)
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
	FILE *fp;
	char buff[255];
	int slidingWindow[3];
	int windowSize = 0;
	int i = 0;

	fopen_s(&fp, "input.txt", "r");


	int currentDepth;
	int currentSum = NULL;
	int prevSum = NULL;
	int increasingMeasCount = 0;

	while (fgets(buff, 255, (FILE*)fp))
	{
		sscanf_s(buff, "%d", &currentDepth);

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

		if (prevSum)
		{
			if (currentSum > prevSum)
			{
				increasingMeasCount++;
			}
		}

		if (currentSum)
		{
			prevSum = currentSum;
		}

	}

	printf("Answer: %d\n", increasingMeasCount);

	fclose(fp);
}
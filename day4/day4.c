
#include <stdio.h>
#include <string.h>

void problem1();
void problem2();

#define bingoBoardHeight 5
#define bingoBoardWidth 5
#define nBoards 100

void printBoard(int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth], int i);
void printBoards(int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth]);
int updateAndCheckForWinningBoard(
	int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth],
	int numberDrawn);
int updateAndCheckForAllWinningBoards(
	int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth],
	int numberDrawn,
	int boardIndicesAlreadyWon[nBoards],
	int* nBoardsAlreadyWon);

int main()
{
	//problem1();
	problem2();
}

void problem1()
{
	char drawnNumbers[511];
	int number;

	int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth] = {0};

	FILE *filePointer = fopen("input.txt", "r");

	if (fscanf(filePointer, "%s", drawnNumbers) == 1)
	{
		//printf("Drawn numbers: %s\n", drawnNumbers);
	}
	else
	{
		printf("Error!\n");
	}

	int rowCount = 0;
	int colCount = 0;
	int boardCount = 0;
	while (fscanf(filePointer, "%d", &number) == 1)
	{
		//printf("%d\n", number);
		bingoBoardsAndMasks[boardCount][0][rowCount][colCount] = number;

		if (rowCount == (bingoBoardHeight - 1) && colCount == (bingoBoardWidth - 1))
		{
			boardCount++;
			rowCount = 0;
			colCount = 0;
		}
		else if(colCount == 4)
		{
			rowCount++;
			colCount = 0;
		}
		else
		{
			colCount++;
		}
	}

	int winningBoard = -1;
	int numberDrawn;
	int i = 0;
	while (winningBoard == -1)
	{
		char buffer[255] = { 0 };
		int j = 0;
		char currentChar = -1;

		while (currentChar != ',' && currentChar != '\0')
		{
			currentChar = drawnNumbers[i];
			buffer[j] = currentChar;
			i++;
			j++;
		}

		sscanf(buffer, "%d", &numberDrawn);
		printf("Number drawn: %d\n", numberDrawn);
		

		winningBoard = updateAndCheckForWinningBoard(bingoBoardsAndMasks, numberDrawn);
	}


	int lastNumberCalled = numberDrawn;
	int sumOfUnmarkedNumbers = 0;
	for (int y = 0; y < bingoBoardHeight; y++)
	{
		for (int x = 0; x < bingoBoardWidth; x++)
		{
			if (bingoBoardsAndMasks[winningBoard][1][y][x] == 0)
			{
				sumOfUnmarkedNumbers += bingoBoardsAndMasks[winningBoard][0][y][x];
			}
		}
	}


	printf("\n\n\nAnswer: %d (sumOfUnmarkedNumbers) * %d (lastNumberCalled) = %d\n", sumOfUnmarkedNumbers, lastNumberCalled, sumOfUnmarkedNumbers*lastNumberCalled);

	fclose(filePointer);
}

int updateAndCheckForWinningBoard(int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth], int numberDrawn)
{
	int winningBoard = -1;

	for (int i = 0; i < nBoards; i++)
	{
		int numberHitY = -1;
		int numberHitX = -1;

		// Update
		for (int y = 0; y < bingoBoardHeight; y++)
		{
			for (int x = 0; x < bingoBoardWidth; x++)
			{
				if (bingoBoardsAndMasks[i][0][y][x] == numberDrawn)
				{
					bingoBoardsAndMasks[i][1][y][x] = 1;
					numberHitY = y;
					numberHitX = x;
				}
			}
		}

		if (numberHitY != -1) {
			// Check if board won by checking row and column of hit number
			int boardWonHorizontal = 1;
			int boardWonVertical = 1;

			// Check row
			for (int x = 0; x < bingoBoardWidth; x++)
			{
				if (bingoBoardsAndMasks[i][1][numberHitY][x] == 0)
				{
					boardWonHorizontal = 0;
					break;
				}
			}

			// Check column
			for (int y = 0; y < bingoBoardHeight; y++)
			{
				if (bingoBoardsAndMasks[i][1][y][numberHitX] == 0)
				{
					boardWonVertical = 0;
					break;
				}
			}

			if (boardWonHorizontal || boardWonVertical)
			{
				winningBoard = i;
				if (boardWonHorizontal)
				{
					printf("Board number %d won horizontally on row %d!\n", winningBoard+1, numberHitY+1);
				}
				else
				{
					printf("Board number %d won vertically on column %d!\n", winningBoard+1, numberHitX+1);
				}
				break;
			}
		}
	}

	return winningBoard;
}

void printBoard(int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth], int i) {

	printf("\n");
	for (int y = 0; y < bingoBoardHeight; y++)
	{
		for (int x = 0; x < bingoBoardWidth; x++)
		{
			printf("%d\t", bingoBoardsAndMasks[i][0][y][x]);
		}
		printf("\n");
	}
	printf("\n");
	
}

void printBoards(int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth]) {
	for (int i = 0; i < nBoards; i++)
	{
		printf("\n\n");
		for (int y = 0; y < bingoBoardHeight; y++)
		{
			for (int x = 0; x < bingoBoardWidth; x++)
			{
				printf("%d\t", bingoBoardsAndMasks[i][1][y][x]);
			}
			printf("\n");
		}
	}
}

void problem2()
{
	char drawnNumbers[511];
	int number;

	int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth] = { 0 };

	FILE *filePointer = fopen("input.txt", "r");

	if (fscanf(filePointer, "%s", drawnNumbers) == 1)
	{
		//printf("Drawn numbers: %s\n", drawnNumbers);
	}
	else
	{
		printf("Error!\n");
	}

	int rowCount = 0;
	int colCount = 0;
	int boardCount = 0;
	while (fscanf(filePointer, "%d", &number) == 1)
	{
		//printf("%d\n", number);
		bingoBoardsAndMasks[boardCount][0][rowCount][colCount] = number;

		if (rowCount == (bingoBoardHeight - 1) && colCount == (bingoBoardWidth - 1))
		{
			boardCount++;
			rowCount = 0;
			colCount = 0;
		}
		else if (colCount == 4)
		{
			rowCount++;
			colCount = 0;
		}
		else
		{
			colCount++;
		}
	}

	int winningBoard = -1;
	int numberDrawn;
	int i = 0;
	int boardIndicesAlreadyWon[nBoards] = { -1 };
	int nBoardsAlreadyWon = 0;
	while (winningBoard == -1 || nBoardsAlreadyWon < nBoards - 1)
	{
		char buffer[255] = { 0 };
		int j = 0;
		char currentChar = -1;

		while (currentChar != ',' && currentChar != '\0')
		{
			currentChar = drawnNumbers[i];
			buffer[j] = currentChar;
			i++;
			j++;
		}

		sscanf(buffer, "%d", &numberDrawn);
		printf("Number drawn: %d\n", numberDrawn);


		winningBoard = updateAndCheckForAllWinningBoards(bingoBoardsAndMasks, numberDrawn, boardIndicesAlreadyWon, &nBoardsAlreadyWon);
	}


	int lastNumberCalled = numberDrawn;
	int sumOfUnmarkedNumbers = 0;
	for (int y = 0; y < bingoBoardHeight; y++)
	{
		for (int x = 0; x < bingoBoardWidth; x++)
		{
			if (bingoBoardsAndMasks[winningBoard][1][y][x] == 0)
			{
				sumOfUnmarkedNumbers += bingoBoardsAndMasks[winningBoard][0][y][x];
			}
		}
	}


	printf("\n\n\nAnswer: %d (sumOfUnmarkedNumbers) * %d (lastNumberCalled) = %d\n", sumOfUnmarkedNumbers, lastNumberCalled, sumOfUnmarkedNumbers*lastNumberCalled);

	fclose(filePointer);
}

int updateAndCheckForAllWinningBoards(int bingoBoardsAndMasks[nBoards][2][bingoBoardHeight][bingoBoardWidth], int numberDrawn, int boardIndicesAlreadyWon[nBoards], int* nBoardsAlreadyWon)
{
	int winningBoard = -1;

	for (int i = 0; i < nBoards; i++)
	{
		// Skip current board if it has already won
		int boardAlreadyWon = 0;
		for (int j = 0; j < nBoards; j++)
		{
			if (i == boardIndicesAlreadyWon[j])
			{
				boardAlreadyWon = 1;
				break;
			}
		}
		if (boardAlreadyWon)
		{
			continue;
		}

		int numberHitY = -1;
		int numberHitX = -1;

		// Update
		for (int y = 0; y < bingoBoardHeight; y++)
		{
			for (int x = 0; x < bingoBoardWidth; x++)
			{
				if (bingoBoardsAndMasks[i][0][y][x] == numberDrawn)
				{
					bingoBoardsAndMasks[i][1][y][x] = 1;
					numberHitY = y;
					numberHitX = x;
				}
			}
		}

		if (numberHitY != -1) {
			// Check if board won by checking row and column of hit number
			int boardWonHorizontal = 1;
			int boardWonVertical = 1;

			// Check row
			for (int x = 0; x < bingoBoardWidth; x++)
			{
				if (bingoBoardsAndMasks[i][1][numberHitY][x] == 0)
				{
					boardWonHorizontal = 0;
					break;
				}
			}

			// Check column
			for (int y = 0; y < bingoBoardHeight; y++)
			{
				if (bingoBoardsAndMasks[i][1][y][numberHitX] == 0)
				{
					boardWonVertical = 0;
					break;
				}
			}

			if (boardWonHorizontal || boardWonVertical)
			{
				winningBoard = i;
				boardIndicesAlreadyWon[*nBoardsAlreadyWon] = winningBoard;
				(*nBoardsAlreadyWon)++;
				if (boardWonHorizontal)
				{
					printf("Board number %d won horizontally on row %d!\n", winningBoard + 1, numberHitY + 1);
				}
				else
				{
					printf("Board number %d won vertically on column %d!\n", winningBoard + 1, numberHitX + 1);
				}
			}
		}
	}

	return winningBoard;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "includes.h"

void init();
void findMoves(int x, int y, int *num_moves, int **moves_arr);
void executeMove(int x, int y, int dX, int dY);
void addToResizableArray(int currX, int currY, int *num_moves, int **moves_arr);
void searchAndExecute(bool player);

#define NUMBER_OF_STATES 13
#define MAX_MOVES 21

#define EMPTYSPACE 0
#define WHITEPAWN 1
#define BLACKPAWN 2
#define WHITEKNIGHT 3
#define BLACKKNIGHT 4
#define WHITEFORTRESS 5
#define BLACKFORTRESS 6
#define WHITEHORSE 7
#define BLACKHORSE 8
#define WHITEQUEEN 9
#define BLACKQUEEN 10
#define WHITEKING 11
#define BLACKKING 12

// prvi je vrstica, drugi je stolpec
int board[8][8] = {
	{5, 7, 3, 9, 11, 3, 7, 5},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{2, 2, 2, 2, 2, 2, 2, 2},
	{6, 8, 4, 10, 12, 4, 8, 6}};

bool castlingPossible0[2] = {true, true};

typedef struct
{
	int n;
	int delta[8][2];
	bool scalable;
} PieceMoves;

PieceMoves moves[NUMBER_OF_STATES];

bool player = 0;

int main()
{
	init();

	disableCursorBlinking();

	printScreen("bitChess");

	bool end = false;
	while (!end)
	{
		printBoard(player, board);
		searchAndExecute(player);
		player = !player;
	}
}

void init()
{

	int moves0[1][2] = {{0, 1}};
	int moves1[1][2] = {{0, -1}};
	int moves2[4][2] = {{1, 1}, {-1, 1}, {-1, -1}, {-1, 1}};
	int moves3[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int moves4[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};
	int moves5[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

	moves[0].n = 0;
	moves[1].n = 0;
	moves[2].n = 0;
	moves[3].n = 4;
	moves[4].n = 4;
	moves[5].n = 4;
	moves[6].n = 4;
	moves[7].n = 8;
	moves[8].n = 8;
	moves[9].n = 8;
	moves[10].n = 8;
	moves[11].n = 8;
	moves[12].n = 8;

	// length 1
	for (int i = 0; i < sizeof(moves0) / sizeof(int[2]); i++)
	{
		moves[1].delta[i][0] = moves0[i][0];
		moves[1].delta[i][1] = moves0[i][1];
		moves[2].delta[i][0] = moves1[i][0];
		moves[2].delta[i][1] = moves1[i][1];
	}

	// length 4
	for (int i = 0; i < sizeof(moves2) / sizeof(int[2]); i++)
	{
		moves[3].delta[i][0] = moves2[i][0];
		moves[3].delta[i][1] = moves2[i][1];
		moves[4].delta[i][0] = moves2[i][0];
		moves[4].delta[i][1] = moves2[i][1];

		moves[5].delta[i][0] = moves3[i][0];
		moves[5].delta[i][1] = moves3[i][1];
		moves[6].delta[i][0] = moves3[i][0];
		moves[6].delta[i][1] = moves3[i][1];
	}

	// length 8
	for (int i = 0; i < sizeof(moves4) / sizeof(int[2]); i++)
	{
		moves[7].delta[i][0] = moves4[i][0];
		moves[7].delta[i][1] = moves4[i][1];
		moves[8].delta[i][0] = moves4[i][0];
		moves[8].delta[i][1] = moves4[i][1];

		moves[9].delta[i][0] = moves5[i][0];
		moves[9].delta[i][1] = moves5[i][1];
		moves[10].delta[i][0] = moves5[i][0];
		moves[10].delta[i][1] = moves5[i][1];

		moves[11].delta[i][0] = moves5[i][0];
		moves[11].delta[i][1] = moves5[i][1];
		moves[12].delta[i][0] = moves5[i][0];
		moves[12].delta[i][1] = moves5[i][1];
	}

	moves[0].scalable = false;
	moves[1].scalable = false;
	moves[2].scalable = false;
	moves[3].scalable = true;
	moves[4].scalable = true;
	moves[5].scalable = true;
	moves[6].scalable = true;
	moves[7].scalable = false;
	moves[8].scalable = false;
	moves[9].scalable = true;
	moves[10].scalable = true;
	moves[11].scalable = false;
	moves[12].scalable = false;
}

void findMoves(int x, int y, int *num_moves, int **moves_arr)
{
	int piece = board[x][y];

	if (board[x][y] == 0)
	{
		//
	}
	else
	{
		if (piece == WHITEPAWN)
		{
			if (x == 1 && (board[x + 2][y] == 0 || (board[x + 2][y + 0] + piece) % 2))
				addToResizableArray(2, 0, num_moves, moves_arr);

			if (board[x + 1][y] == 0 || (board[x + 1][y] + piece) % 2)
				addToResizableArray(1, 0, num_moves, moves_arr);

			// CAPTURING SIDEWAYS
			if (board[x + 1][y + 1] != 0 && ((board[x + 1][y + 1] + piece) % 2))
				addToResizableArray(1, 1, num_moves, moves_arr);

			if (board[x + 1][y - 1] != 0 && ((board[x + 1][y - 1] + piece) % 2))
				addToResizableArray(1, -1, num_moves, moves_arr);
		}
		else if (piece == BLACKPAWN)
		{

			if (x == 6 && (board[x - 2][y] == 0 || (board[x - 2][y + 0] + piece) % 2))
				addToResizableArray(-2, 0, num_moves, moves_arr);

			if (board[x - 1][y] == 0 || (board[x - 1][y] + piece) % 2)
				addToResizableArray(-1, 0, num_moves, moves_arr);

			// CAPTURING SIDEWAYS
			if (board[x - 1][y + 1] != 0 && ((board[x - 1][y + 1] + piece) % 2))
				addToResizableArray(1, -1, num_moves, moves_arr);

			if (board[x - 1][y - 1] != 0 && ((board[x - 1][y - 1] + piece) % 2))
				addToResizableArray(-1, -1, num_moves, moves_arr);
		}
		else
		{
			for (int i = 0; i < moves[piece].n; i++)
			{
				int currX = moves[piece].delta[i][0];
				int currY = moves[piece].delta[i][1];

				while (x + currX >= 0 && x + currX < 8 && y + currY >= 0 && y + currY < 8)
				{
					if (board[x + currX][y + currY] == 0)
						addToResizableArray(currX, currY, num_moves, moves_arr);

					else if ((board[x + currX][y + currY] + piece) % 2)
					{
						addToResizableArray(currX, currY, num_moves, moves_arr);
						break;
					}
					else
						break;

					if (!moves[piece].scalable)
						break;

					currX += moves[piece].delta[i][0];
					currY += moves[piece].delta[i][1];
				}
			}
		}
	}

	// special moves...
	//---------------------------------------------------------------------

	// CASTING
	// return special vector - we have right and left castling also!!

	// EN PASSANT - we have rigth and lefto ones!!

	// PROMOTION
	// return special vector - a piece from all the pieces needs to be chosen

	//---------------------------------------------------------------------
}

bool possibleMove(int xs, int ys, int xe, int ye)
{
	int piece = board[xs][ys];

	if (board[xs][ys] == 0)
	{
		// empty square
		return false;
	}
	else if (piece == WHITEPAWN)
	{
		if (xe == xs + 1 && ye == ys && board[xe][ye] == 0)
		{
			return true;
		}
		else if (xe == xs + 2 && ys == ye && xs == 1 && board[xe][ye] == 0 && board[xs + 1][ys] == 0)
		{
			return true;
		}
		else if (xe == xs + 1 && abs(ye - ys) == 1 && board[xe][ye] != 0 && (board[xe][ye] + piece) % 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (piece == BLACKPAWN)
	{
		if (xe == xs - 1 && ye == ys && board[xe][ye] == 0)
		{
			return true;
		}
		else if (xe == xs - 2 && ys == ye && xs == 6 && board[xe][ye] == 0 && board[xs - 1][ys] == 0)
		{
			return true;
		}
		else if (xe == xs - 1 && abs(ye - ys) == 1 && board[xe][ye] != 0 && (board[xe][ye] + piece) % 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		// check for other pieces
		// ...
	}

	return false;

	// special moves...
	//---------------------------------------------------------------------

	// CASTING
	// return special vector - we have right and left castling also!!

	// EN PASSANT - we have rigth and lefto ones!!

	// PROMOTION
	// return special vector - a piece from all the pieces needs to be chosen

	//---------------------------------------------------------------------
}

void executeMove(int xs, int ys, int xe, int ye)
{
	int piece = board[ys][xs];
	board[ys][xs] = 0;
	// here implement castling
	//...
	board[ye][xe] = piece;
}

void searchAndExecute(bool player)
{
	char xS, yS, xE, yE;

	int xs, ys, xe, ye;

	// resizable array
	int *moves_arr = malloc(sizeof(int) * 2 * MAX_MOVES);
	if (moves_arr == NULL)
	{
		printf("Memory allocation failed\n");
		return;
	}

	int num_moves = 0;

	do
	{
		getMoves(&xS, &yS, &xE, &yE);

		xs = charToCordX(xS);
		xe = charToCordX(xE);
		ys = charToCordY(yS);
		ye = charToCordY(yE);

		// is the figure in bounds
		if ((xs < 0 || xs > 7 || ys < 0 || ys > 7) ||
			(xe < 0 || xe > 7 || ye < 0 || ye > 7))
		{
			Warning(1);
			continue;
		}

		// empty space
		if (board[ys][xs] == EMPTYSPACE)
		{
			Warning(2);
			continue;
		}

		// is it even my figure
		if ((board[ys][xs] % 2) == player)
		{
			Warning(3);
			continue;
		}

		findMoves(ys, xs, &num_moves, &moves_arr);

		bool foundIt = false;
		for (int i = 0; i < num_moves; i++)
		{
			if (moves_arr[2 * i + 1] == xe - xs && moves_arr[2 * i] == ye - ys)
			{
				foundIt = true;
				break;
			}
		}

		if (foundIt)
			break;

		// if (possibleMove(ys, xs, ye, xe))
		// 	break;

		printf("Move not possible!\n");

	} while (true);

	// free(moves_arr);

	executeMove(xs, ys, xe, ye);

	// write_moves(xS, yS, xE, yE);
}

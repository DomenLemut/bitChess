#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define NUMBER_OF_STATES 13

const char *str[NUMBER_OF_STATES] = {
    "  ",
    "\u265F ",
    "\u2659 ",
    "\u265D ",
    "\u2657 ",
    "\u265C ",
    "\u2656 ",
    "\u265E ",
    "\u2658 ",
    "\u265B ",
    "\u2655 ",
    "\u265A ",
    "\u2654 "};

void printBoard(bool player, int board[8][8])
{
    if (player == 1)
    {
        for (int y = 0; y < 8; y++)
        {
            printf("%d ", y + 1);
            for (int x = 0; x < 8; x++)
            {
                printf("%s", str[board[y][x]]);
            }
            printf("\n");
        }
    }
    else
    {
        for (int y = 7; y >= 0; y--)
        {
            printf("%d ", y + 1);
            for (int x = 0; x < 8; x++)
            {
                printf("%s", str[board[y][x]]);
            }
            printf("\n");
        }
    }

    printf("  ");
    for (int i = 0; i < 8; i++)
    {
        printf("%c ", 'A' + i);
    }
    printf("\n\n\n");
}

void clearScrn()
{
    printf("\033[2J");
    printf("\033[1;1H");
}

void playAnimation()
{
}

void enableCursorBlinking()
{
    printf("\033[?25h");
}

void disableCursorBlinking()
{
    printf("\033[?25l");
}

int getMove()
{
    int move = -1;

    printf("Select the move you want to do: ");
    enableCursorBlinking();

    scanf("%d", &move);
    move--;

    disableCursorBlinking();
    return move;
}

void getStartingPoint(char *xC, char *yC)
{
    printf("Select the piece you want to move[A1, F6... ?]: ");

    enableCursorBlinking();
    scanf(" %c%c", xC, yC);

    disableCursorBlinking();
}

void printCheckScreen()
{
    int timeU = 150000;
    clearScrn();
    printf("%s", "\n\n\n     C              \n\n\n\n");
    usleep(timeU);
    clearScrn();
    printf("%s", "\n\n\n     CH             \n\n\n\n");
    usleep(timeU);
    clearScrn();
    printf("%s", "\n\n\n     CHE            \n\n\n\n");
    usleep(timeU);
    clearScrn();
    printf("%s", "\n\n\n     CHEC           \n\n\n\n");
    usleep(timeU);
    clearScrn();
    printf("%s", "\n\n\n     CHECK          \n\n\n\n");
    usleep(timeU);
    clearScrn();
    printf("%s", "\n\n\n     CHECK!         \n\n\n\n");
    usleep(timeU);
    clearScrn();
    printf("%s", "\n\n\n     CHECK!!        \n\n\n\n");
    usleep(3 * timeU);
}
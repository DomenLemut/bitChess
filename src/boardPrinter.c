#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define NUMBER_OF_STATES 13

#define REDBACK "\x1B[101m"
#define GREENBACK "\x1B[102m"
#define YELLOWBACK "\x1B[103m"
#define BLUEBACK "\x1B[104m"
#define MAGBACK "\x1B[105m"
#define CYANBACK "\x1B[106m"

#define BACKGROUNDCOL YELLOWBACK

void clearScrn();

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
    clearScrn();

    if (player == 1)
    {
        for (int y = 0; y < 8; y++)
        {
            printf("%d ", y + 1);
            for (int x = 0; x < 8; x++)
            {
                if ((x + y) % 2)
                    printf(BACKGROUNDCOL);
                printf("%s", str[board[y][x]]);

                printf("\x1B[0m");
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
                if ((x + y) % 2)
                    printf(BACKGROUNDCOL);
                printf("%s", str[board[y][x]]);

                printf("\x1B[0m");
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

void enableCursorBlinking()
{
    printf("\033[?25h");
}

void disableCursorBlinking()
{
    printf("\033[?25l");
}

void getMoves(char *xS, char *yS, char *xE, char *yE)
{

    printf("Your move: ");

    enableCursorBlinking();

    char curr = '?';

    do
    {
        curr = getchar();
    } while (curr < 'A' || curr > 'I');
    *xS = curr;

    do
    {
        curr = getchar();
    } while (curr < '1' || curr >= '9');
    *yS = curr;

    do
    {
        curr = getchar();
    } while (curr < 'A' || curr > 'I');
    *xE = curr;

    do
    {
        curr = getchar();
    } while (curr < '1' || curr >= '9');
    *yE = curr;

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
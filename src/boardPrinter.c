#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define NUMBER_OF_STATES 13

#define HORISONTAL_LINE "\u2500"
#define VERTICAL_LINE "\u2502"
#define TOP_LEFT_CORNER "\u250c"
#define TOP_RIGTH_CORNER "\u2510"
#define BOTTOM_LEFT_CORNER "\u2514"
#define BOTTOM_RIGTH_CORNER "\u2518"

#define REDBACK "\x1B[101m"
#define GREENBACK "\x1B[102m"
#define YELLOWBACK "\x1B[103m"
#define BLUEBACK "\x1B[104m"
#define MAGBACK "\x1B[105m"
#define CYANBACK "\x1B[106m"

#define NORMALBACK "\x1B[0m"

#define BACKGROUNDCOL YELLOWBACK

// printing spacing variables
#define BOX_HEIGHT 12
#define BOX_WIDTH 100

#define BOARD_START_H 1
#define BOARD_START_W 2
#define BOARD_WIDTH 18
#define BOARD_HEIGHT 18

#define SEPARATION 4

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

typedef struct
{
    char *BUFFER[BOX_WIDTH];
    int cntSimbols;
    int cntChars;
} Buffer;

Buffer initBuffer()
{
    Buffer buffer;
    buffer.cntChars, buffer.cntSimbols = 0;
    return buffer;
}

void addToBuffer(Buffer *buffer, char *str)
{
    int len = strlen(str);
    if (buffer->cntChars + len > BOX_WIDTH)
    {
        // The string doesn't fit into the buffer
        return;
    }
    int i, j;
    for (i = 0; i < len; i++)
    {
        // Add each character of the string to the buffer
        buffer->BUFFER[buffer->cntSimbols] = malloc(sizeof(char));
        *(buffer->BUFFER[buffer->cntSimbols]) = str[i];
        buffer->cntSimbols++;
    }
    buffer->cntChars += len;
}

void printBoard(bool player, int board[8][8])
{
    clearScrn();

    Buffer buffer = initBuffer();

    int boxWidth = 36;
    int boxHeight = 12;

    int boxHeightCount = 0;

    for (int y = 0; y < BOX_HEIGHT; y++)
    {

        if (y < 9 && y > 0)
        {
            int bY = y - 1;
            if (!player)
            {
                printf("%d ", y);
                for (int x = 0; x < 8; x++)
                {
                    if ((x + bY) % 2)
                        printf(BACKGROUNDCOL);
                    printf("%s", str[board[bY][x]]);

                    printf("\x1B[0m");
                }
            }
            else
            {
                printf("%d ", y);
                for (int x = 7; x >= 0; x--)
                {
                    if ((x + bY) % 2)
                        printf(BACKGROUNDCOL);
                    printf("%s", str[board[bY][x]]);

                    printf("\x1B[0m");
                }
            }
        }

        if (y > 9 || y < 1)
        {
            for (int i = 0; i < 18; i++)
                printf(" ");
        }
        else if (y == 9)
        {
            printf("  ");
            for (int i = 0; i < 8; i++)
                printf("%c ", 'A' + i);
        }

        if (boxHeightCount < boxHeight)
        {
            for (int i = 0; i < 4; i++)
                printf(" ");

            if (boxHeightCount == 0)
            {
                printf("%s", TOP_LEFT_CORNER);
                for (int i = 0; i < boxWidth - 2; i++)
                    printf("%s", HORISONTAL_LINE);

                printf("%s", TOP_RIGTH_CORNER);
            }

            else if (boxHeightCount == boxHeight - 1)
            {
                printf("%s", BOTTOM_LEFT_CORNER);
                for (int i = 0; i < boxWidth - 2; i++)
                    printf("%s", HORISONTAL_LINE);

                printf("%s", BOTTOM_RIGTH_CORNER);
            }
            else
            {
                printf("%s", VERTICAL_LINE);
                for (int i = 0; i < boxWidth - 2; i++)
                    printf(" ");
                printf("%s", VERTICAL_LINE);
            }

            boxHeightCount++;
        }

        printf("\n");
    }
    printf("\n");
}

void printBuffer(Buffer *buffer)
{
}

void clearScrn()
{
    printf("\033[2J");
    printf("\033[1;1H");
}

void Warning(int warning)
{
    switch (warning)
    {
    case 1:
        printf("Invalid entry\n");
        break;
    case 2:
        printf("This is an empty space\n");
        break;
    case 3:
        printf("This is not your figure\n");
        break;
    default:
        printf("invalid warn");
    }
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

void printScreen(char *str)
{
    int timeU = 150000;

    for (int i = 1; i < strlen(str) + 2; i++)
    {
        clearScrn();
        printf("\n\n\n\n      %.*s \n", i, str);
        usleep(timeU);
    }

    usleep(3 * timeU);
}

void Box()
{
    clearScrn();
    char *arr[12][24];

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            arr[i][j] = " ";
        }
    }

    arr[0][0] = TOP_LEFT_CORNER;
    arr[0][23] = TOP_RIGTH_CORNER;
    arr[11][0] = BOTTOM_LEFT_CORNER;
    arr[11][23] = BOTTOM_RIGTH_CORNER;

    for (int i = 1; i < 23; i++)
    {
        arr[0][i] = HORISONTAL_LINE;
        arr[11][i] = HORISONTAL_LINE;
    }

    for (int i = 1; i < 11; i++)
    {
        arr[i][0] = VERTICAL_LINE;
        arr[i][23] = VERTICAL_LINE;
    }

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            printf("%s", arr[i][j] ? arr[i][j] : " ");
        }
        printf("\n");
    }

    sleep(5);
}
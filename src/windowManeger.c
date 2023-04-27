#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    bool box;
    int width, height, startW, startH;
    char ***matrix;
} window;

bool addToWindows(window win);
void addBorders(window win);
void printWindows();

#define MAX_WINDOWS 10
#define HORISONTAL_LINE "\u2500"
#define VERTICAL_LINE "\u2502"
#define TOP_LEFT_CORNER "\u250c"
#define TOP_RIGTH_CORNER "\u2510"
#define BOTTOM_LEFT_CORNER "\u2514"
#define BOTTOM_RIGTH_CORNER "\u2518"

window windows[MAX_WINDOWS];
int numWindows;

window makeNewWindow(int width, int height, int startW, int startH, bool borders)
{
    window new;
    new.width = width;
    new.height = height;
    new.startW = startW;
    new.startH = startH;
    new.matrix = (char ***)malloc(height * sizeof(char **));
    for (int i = 0; i < height; i++)
    {
        new.matrix[i] = (char **)malloc(width * sizeof(char *));
        for (int j = 0; j < width; j++)
        {
            new.matrix[i][j] = (char *)malloc(10 * sizeof(char));
        }
    }
    if (borders)
        addBorders(new);
    return new;
}

bool addToWindows(window win)
{
    if (numWindows < MAX_WINDOWS)
    {
        windows[numWindows] = win;
        numWindows++;
        return true;
    }
    return false;
}

void addBorders(window win)
{
    win.matrix[0][0] = TOP_LEFT_CORNER;
    for (int i = 1; i < win.width - 1; i++)
    {
        win.matrix[0][i] = HORISONTAL_LINE;
    }
    win.matrix[win.width - 1][0] = TOP_RIGTH_CORNER;
    for (int i = 1; i < win.height - 1; i++)
    {
        win.matrix[i][win.width - 1] = VERTICAL_LINE;
    }
    win.matrix[win.height - 1][win.width - 1] = BOTTOM_RIGTH_CORNER;
    for (int i = 1; i < win.width - 1; i++)
    {
        win.matrix[win.height - 1][i] = HORISONTAL_LINE;
    }
    win.matrix[win.height - 1][0] = BOTTOM_LEFT_CORNER;
    for (int i = 1; i < win.height - 1; i++)
    {
        win.matrix[i][0] = VERTICAL_LINE;
    }
}

void printWindows()
{
    int i, j, k;

    for (i = 0; i < numWindows; i++)
    {
        // Print the top border of the window
        for (j = 0; j < windows[i].width; j++)
        {
            printf("%s", windows[i].matrix[0][j]);
        }
        printf("\n");

        // Print the content of the window
        for (j = 1; j < windows[i].height - 1; j++)
        {
            printf("%s", windows[i].matrix[j][0]);
            for (k = 1; k < windows[i].width - 1; k++)
            {
                printf("%s", windows[i].matrix[j][k]);
            }
            printf("%s\n", windows[i].matrix[j][windows[i].width - 1]);
        }

        // Print the bottom border of the window
        for (j = 0; j < windows[i].width; j++)
        {
            printf("%s", windows[i].matrix[windows[i].height - 1][j]);
        }
        printf("\n");
    }
}

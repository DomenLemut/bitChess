#ifndef WINDOW_H
#define WINDOW_H

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
window makeNewWindow(int width, int height, int startW, int startH, bool borders);
bool addToWindows(window win);
void addBorders(window win);

#define MAX_WINDOWS 10
#define HORISONTAL_LINE "\u2500"
#define VERTICAL_LINE "\u2502"
#define TOP_LEFT_CORNER "\u250c"
#define TOP_RIGTH_CORNER "\u2510"
#define BOTTOM_LEFT_CORNER "\u2514"
#define BOTTOM_RIGTH_CORNER "\u2518"

#endif // WINDOW_H

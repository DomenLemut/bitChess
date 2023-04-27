#include <stdbool.h>

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
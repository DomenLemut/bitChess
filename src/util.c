#include <stdio.h>
#include <stdlib.h>

void addToResizableArray(int currX, int currY, int *num_moves, int **moves_arr)
{
    (*moves_arr)[*num_moves * 2] = currX;
    (*moves_arr)[*num_moves * 2 + 1] = currY;
    (*num_moves)++;
}
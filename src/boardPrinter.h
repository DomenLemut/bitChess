#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#define NUMBER_OF_STATES 13

extern const char *str[NUMBER_OF_STATES];

extern void printBoard(bool player, int board[8][8]);

extern void clearScrn();

extern void enableCursorBlinking();

extern void disableCursorBlinking();

extern void getMoves(char *xS, char *yS, char *xE, char *yE);

extern void printScreen(char *str);

extern void Box();

extern void Warning(int warning);

#endif /* CHESS_H */
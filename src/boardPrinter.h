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

void clearScrn();
void printBoard(bool player, int board[8][8]);
void enableCursorBlinking();
void disableCursorBlinking();
void getMoves(char *xS, char *yS, char *xE, char *yE);
void printScreen(char *str);
void Box();


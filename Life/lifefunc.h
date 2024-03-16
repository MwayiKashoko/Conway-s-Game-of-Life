//lifefunc.h
#define SIZE 40

void drawBorder();
void drawBoard(char arr[SIZE][SIZE]);
int simulateNeighborArray(char arr[SIZE][SIZE], int row, int col);
char simulateBoard(int neighbors, bool occupied);
void interactiveMode();
void batchMode(char str[]);

//lifefunc.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lifefunc.h"

//To avoid redundancies in the drawBoard function
void drawBorder() {
	for (int i = 0; i < SIZE*2; i++) {
		printf("-");
	}
}

//Draws the board which consists of the characters | _ ' ' X
void drawBoard(char arr[SIZE][SIZE]) {
	printf(" ");
	drawBorder();

	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		printf("|");

		for (int j = 0; j < SIZE; j++) {
			printf("%c ", arr[i][j]);
		}

		printf("|");
		printf("\n");
	}

	printf(" ");
	drawBorder();

	printf("\n");
}

//Updates the neighbor array (holds the number of neighbors each cell has)
int simulateNeighborArray(char arr[SIZE][SIZE], int row, int col) {
	int neighbors = 0;

	for (int i = row-1; i < row+2; i++) {
		for (int j = col-1; j < col+2; j++) {
			//Checking boundries and also checking to make sure that the cell itself is not included in the neighbor count
			if (i >= 0 && i <= 39  && j >= 0 && j <= 39 && (i != row || j != col)) {
				if (arr[i][j] == 'X') {
					neighbors++;
				}
			}
		}
	}

	return neighbors;
}

//Logic to see whether a cell should become alive or dead
char simulateBoard(int neighbors, bool occupied) {
	if (neighbors != 2 && neighbors != 3) {
		return ' ';
	} else if (neighbors == 2 && !occupied) {
		return ' ';
	}

	return 'X';
}

//Runs if the user enters no command line arguments
void interactiveMode() {
	//The board you see displayed to the screen each iteration
	char board[SIZE][SIZE] = {0};
	//Contains the number of neighbors each cell has
	int neighborArray[SIZE][SIZE] = {0};

	//Initializing each coordinate in each board
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = ' ';
		}
	}

	//user input variable it can not possible have more than 9 characters
	char decision[9];
	char type;
	int row;
	int col;

	//infinite loop where all the conditions happen
	while (1) {
		drawBoard(board);

		printf("Please enter a command: ");
		fgets(decision, 9, stdin);
		decision[strlen(decision)-1] = '\n';
		sscanf(decision, "%c %d %d", &type, &row, &col);

		//adds a cell to a valid coordinate
		if (type == 'a') {
			if (row < 0 || row > 39 || col < 0 || col > 39) {
				printf("INVALID COORDINATE!\n");
				continue;
			}

			board[row][col] = 'X';
		} else if (type == 'r') {
			//removes a cell to a valid coordinate
			if (row < 0 || row > 39 || col < 0 || col > 39) {
				printf("INVALID COORDINATE!\n");
				continue;
			}

			board[row][col] = ' ';
		} else if (type == 'n') {
			//clears the screen and also iterates the next position
			system("clear");

			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					neighborArray[i][j] = simulateNeighborArray(board, i, j);
				}
			}

			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					board[i][j] = simulateBoard(neighborArray[i][j], board[i][j] == 'X');
				}
			}
		} else if (type == 'q') {
			//Quits the entire program
			break;
		} else if (type == 'p') {
			//Continuously runs the program until the user stops it
			while (1) {
				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++) {
						neighborArray[i][j] = simulateNeighborArray(board, i, j);
					}
				}

				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++) {
						board[i][j] = simulateBoard(neighborArray[i][j], board[i][j] == 'X');
					}
				}

				system("clear");
				drawBoard(board);
				usleep(100000);
			}
		}
	}
}

void batchMode(char str[]) {
	FILE *file;
	int arrSize = 10;
	char arr[arrSize];
	int count = 0;

	char board[SIZE][SIZE] = {0};
	int neighborArray[SIZE][SIZE] = {0};

	//Initializing each coordinate in each board
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = ' ';
		}
	}

	//file detection and error handling in one step
	if (!(file = fopen(str, "r"))) {
		printf("Invalid File!\nProgram Will Now Terminate!m\n");
		return;
	}

	while (1) {
		//getting each character per line and then using that to add the cells
		arr[count] = fgetc(file);

		//Checking for the final condition
		if (arr[count] == EOF || arr[count] == 'p') {
			break;
		} else if (arr[count] == '\n') {
			int row;
			int col;

			sscanf(arr, "a %d %d", &row, &col);

			board[row][col] = 'X';
			count = 0;

			//resetting the array and count in order to read the next line
			for (int i = 0; i < arrSize; i++) {
				arr[i] = ' ';
			}
		} else {
			count++;
		}
	}

	//runs forever until the user stops it
	while (1) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				neighborArray[i][j] = simulateNeighborArray(board, i, j);
			}
		}

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				board[i][j] = simulateBoard(neighborArray[i][j], board[i][j] == 'X');
			}
		}

		system("clear");
		drawBoard(board);
		usleep(100000);
	}
}

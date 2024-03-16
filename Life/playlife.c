//playlife.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lifefunc.h"

int main(int argc, char * argv[]) {
	if (argc == 1) {
		interactiveMode();
	} else if (argc == 2) {
		batchMode(argv[1]);
	} else {
		//error
		printf("Invalid Batch Input!\nThe Program Will Now Terminate!\n");
		return -1;
	}

	return 0;
}

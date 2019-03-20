#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "game.h"

//Make sure inputted size is a valid integer
int checkSize(char* size) {
    int numSize = 0;
    int indexHelper = 1;
    int length = strlen(size);

    //Check if string is all digits
    for (int i = 0; i < length; i++) {
        //Return with error if non-digit char is found
        if (!isdigit(size[i])) {
            return -1;
        }
        //Convert size string to integer
        else {
            //temp = char converted into integer
            int temp = (int)size[i] - 48;
            //Build int version of size
            numSize = numSize + (temp * pow(10, length - indexHelper));
            indexHelper++;
        }
    }

    //Words must be at least 3 letters long, so min board size = 2x2
    if (numSize < 2) {
        return -1;
    }

    //Return converted size
    return numSize;
}

void delay(int numSeconds) {
    int milliseconds = 1000 * numSeconds;
    clock_t startTime = clock();
    while(clock() < startTime + milliseconds)
        ;
}


//Initialize the board
boggleBoard** initializeBoard(int size) {
    //Hold all die in an array
    char letterList[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    //Allocate space for the board
    boggleBoard** board = (boggleBoard**) malloc (size * sizeof(boggleBoard*));
    for (int i = 0; i < size; i++) {
        board[i] = (boggleBoard*) malloc (sizeof (boggleBoard) * size);
    }
    //Load the board with random letters
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int randomIndex = rand() % strlen(letterList);
            board[i][j].letter = letterList[randomIndex];
            board[i][j].picked = false;
        }
    }
    return board;
}



//Print board with arbitrary size to screen 
void displayBoard(int size, boggleBoard** board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].letter == 'Q')
                printf("Qu ");
            else
                printf("%c  ", board[i][j].letter);
            board[i][j].letter = tolower(board[i][j].letter);
        }
        printf("\n");
    }
    return;
}



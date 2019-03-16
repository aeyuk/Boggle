#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "game.h"


//Initialize the board
boggleBoard** initializeBoard(int size) {
    //Hold all die in an array
    char letterList[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'
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



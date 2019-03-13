//Specific dice configuration for English Boggle (16 dice)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct boggleBoard {
    char letter; //Holds cube's face value
    int flag;
} boggleBoard;


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
    for (int i = 0; i < size; i++) {                        //Board rows
        for (int j = 0; j < size; j++) {                    //Board cols
            int randomIndex = rand() % strlen(letterList);
            board[i][j].letter = letterList[randomIndex];
        }
    }
    return board;
}


void displayBoard(int size, boggleBoard** board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].letter == 'Q')
                printf("Qu ");
            else
                printf("%c  ", board[i][j].letter);
        }
        printf("\n");
    }
    return;
}


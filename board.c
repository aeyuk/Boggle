#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "game.h"

//Make sure input for size/difficulty is a valid integer
int checkInput(char* input, char* type) {
    int numInput = 0;
    int indexHelper = 1;
    int length = strlen(input);

    //Check if string is all digits
    for (int i = 0; i < length; i++) {
        //Return with error if non-digit char is found
        if (!isdigit(input[i])) {
            return -1;
        }
        //Convert size string to integer
        else {
            //temp = char converted into integer
            int temp = (int)input[i] - 48;
            //Build int version of size
            numInput = numInput + (temp * pow(10, length - indexHelper));
            indexHelper++;
        }
    }
    //Handle size parameters
    if (strncmp(type, "size", 4) == 0) {
        //Words must be at least 3 letters long, so min board size = 2x2
        if (numInput < 2) {
            return -1;
        }
        //Return converted size
        return numInput;
    }
    //Handle difficulty parameters
    else if (strncmp(type, "difficulty", 10) == 0) {
        if (numInput < 1 || numInput > 5) {
            return -1;
        }
        return numInput;
    }
    else {
        return numInput;
    }
}

//Prompt player to enter board size
int promptBoardSize() {
    char tempSize[10];
    printf("Enter size of board (excessively large inputs may disrupt viewing, size 60 guarantees scrolling): \n");
    scanf("%s", tempSize);
    int size = checkInput(tempSize, "size");
    if (size == -1) {
        printf("Error: invalid input.\n\n");
        return promptBoardSize();
    }
    return size;
}


//Prompt player to enter difficulty
int promptDifficulty() {
    char tempDiffculty[10];;
    printf("Choose the difficulty of the computer from 1 to 5, 1 being easiest:\n");
    scanf("%s", tempDiffculty);
    int difficulty = checkInput(tempDiffculty, "difficulty");
    if (difficulty == -1) {
        printf("Error: invalid input.\n\n");
        return promptDifficulty();
    }
    return difficulty;
}


//Free memory
void freeBoggleBoard(boggleBoard** board, int size) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
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
        board[i] = (boggleBoard*) malloc (sizeof(boggleBoard) * size);
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
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("| ");
        for (int j = 0; j < size; j++) {
            if (board[i][j].letter == 'Q')
                printf("Qu");
            else
                printf("%c ", board[i][j].letter);
            if (j == size - 1)
                printf("|");
            board[i][j].letter = tolower(board[i][j].letter);
        }
        printf("\n");
    }
    return;
}



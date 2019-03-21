#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "game.h"

int main(void) {

    //Open dictionary file
    char word[1000];
    FILE *fp;
    fp = fopen("/usr/share/dict/words", "r");
    if (fp == NULL) {
        printf("Error: words file could not be found\n");
        return 1;
    }

    //Create root node
    struct trieNode* root = createTrieNode();


    //Read words file and construct trie
    while (fgets(word, 1000, fp) != NULL) {
        for (int i = 0; i < strlen(word); i++) {
            if (word[i] == '\n') {
                word[i] = '\0';
            }
            //Convert all letters to lowercase
            word[i] = tolower(word[i]);
        }
        insertTrieNode(&root, word);
    }

    //Close file
    fclose(fp);

    //GAME IMPLEMENTATION
    printf("-------WELCOME TO BOGGLE-------\n");

    //Track total games score
    int playerScore = 0;
    int cpuScore = 0;
    char command[20];

    while(strcmp(command, "q") != 0) {
    //Prompt player for board size
    char tempSize[10];
    int size = 0;
    printf("Enter size: \n");
    scanf("%s", tempSize);

    //Halt on invalid input
    if (checkSize(tempSize) == -1) {
        printf("Error: invalid size\n");
        return -1;
    }
    //Convert size to integer
    size = checkSize(tempSize);

    //Create and display board on screen
    boggleBoard** board = initializeBoard(size);
    displayBoard(size, board);

    //Computer: find all possible words on boggle board
    printf("Computer:\n");
    int cpuPoints = computerFindWords(board, size, root);

    //User inputs all found words
    int playerPoints = userFindWords(board, size, root);


    //Print score totals
    printf("\nYou score: %d points\n", playerPoints);
    printf("Computer score: %d points\n\n", cpuPoints);

    //Incrememnt winner's score
    if (cpuPoints > playerPoints) {
        printf("\nComputer wins!\n");
        cpuScore++;
    }
    else if (playerPoints > cpuPoints) {
        printf("\nYou win!\n");
        playerScore++;
    }
    else printf("Tie! No points given\n");

    //Print standings
    printf("\n\nSTANDINGS:\n");
    printf("Player 1: %d \t Computer: %d\n\n", playerScore, cpuScore);

    freeBoggleBoard(board, size);
    extern int wordIndex;

    printf("Play again? (Enter any character to continue; Enter q to stop)\n");
    scanf("%s", command);
    }

}

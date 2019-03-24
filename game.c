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
    //fp = fopen("words_alpha.txt", "r");
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
        insertTrieNode(root, word);
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

    //Prompt player for board size, halt on invalid input
    int size = promptBoardSize();

    //Prompt player for difficulty, halt on invalid input
    int difficulty = promptDifficulty();
    printf("%d\n", difficulty);


    //Create and display board on screen
    boggleBoard** board = initializeBoard(size);
    displayBoard(size, board);


    //Computer: find all possible words on boggle board
    computerFindWords(board, size, root);


    //User: plays and finds words
    //Array holds player points, computer points
    int* pointsArray;

    pointsArray = userFindWords(board, size, root, difficulty);
    int playerPoints = pointsArray[0];
    int cpuPoints = pointsArray[1];

    //Print score totals
    printf("\nYou scored: %d points\n", playerPoints);
    printf("Computer scored: %d points\n\n", cpuPoints);

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


    printf("See the words you missed? (Enter 'y' to see)\n");
    scanf("%s", command);
    if (strcmp(command, "y") == 0) {
        printMissed();
    }


    //Reset game
    freeBoggleBoard(board, size);
    memset(pointsArray, 0, size);


    printf("Play again? (Enter any character to continue; Enter q to stop)\n");
    scanf("%s", command);
    }

}

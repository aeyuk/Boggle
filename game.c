
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

    //Invalid words include proper nouns and any non-alpha chars
    bool properNoun = false;
    bool invalid = false;

    //Read words file and construct trie
    while (fgets(word, 1000, fp) != NULL) {
        //Skip proper nouns
        if ((int)word[0] >= 65 && (int)word[0] <= 90) {
            properNoun = true;
        }
        if (!properNoun) {
            for (int i = 0; i < strlen(word); i++) {
                //Get rid of new lines
                if (word[i] == '\n') {
                    word[i] = '\0';
                }
                //Convert all letters to lowercase
                word[i] = tolower(word[i]);
            }
            if (!invalid)
            insertTrieNode(root, word);
        }
        //Reset flags
        properNoun = false;
        invalid = false;
    }

    //Close file
    fclose(fp);

    system("clear");

    //GAME IMPLEMENTATION

    //Text art generated from http://patorjk.com/software/taag/#p=display&h=1&v=1&f=Blocks&t=Boggle
    printf("------------WELCOME TO------------\n");
    printf(" .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
    printf("| |   ______     | || |     ____     | || |    ______    | || |    ______    | || |   _____      | || |  _________   | |\n");
    printf("| |  |_   _ |    | || |   .'    `.   | || |  .' ___  |   | || |  .' ___  |   | || |  |_   _|     | || | |_   ___  |  | |\n");
    printf("| |    | |_) |   | || |  /  .--.  |  | || | / .'   |_|   | || | / .'   |_|   | || |    | |       | || |   | |_  |_|  | |\n");
    printf("| |    |  __'.   | || |  | |    | |  | || | | |    ____  | || | | |    ____  | || |    | |   _   | || |   |  _|  _   | |\n");
    printf("| |   _| |__) |  | || |  |  `--'  /  | || | | `.___]  _| | || | | `.___]  _| | || |   _| |__/ |  | || |  _| |___/ |  | |\n");
    printf("| |  |_______/   | || |   `.____.'   | || |  `._____.'   | || |  `._____.'   | || |  |________|  | || | |_________|  | |\n");
    printf("| |              | || |              | || |              | || |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n\n");
    //Track total games score
    int playerScore = 0;
    int cpuScore = 0;
    char command[20];

    while(strcmp(command, "q") != 0) {
        //Prompt player for board size, halt on invalid input
        int size = promptBoardSize();

        //Prompt player for difficulty, halt on invalid input
        int difficulty = promptDifficulty();

        //Create and display board on screen
        system("clear");
        printf("-------WELCOME TO BOGGLE-------\n");

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
        printf(".................................................................\n");


        //Incrememnt winner's score, declare winner
        if (cpuPoints > playerPoints) {
            printf("\nComputer wins!\n");
            cpuScore++;
        }
        else if (playerPoints > cpuPoints) {
            printf("\nYou win!\n");
            playerScore++;
        }
        else printf("Tie! No points given\n");


        printf("\n.................................................................\n");


        //Print standings
        printf("\n\nSTANDINGS:\n");
        printf("Player 1: %d \t Computer: %d\n\n", playerScore, cpuScore);

        printf(".................................................................\n");

        //Print words missed by user
        printf("See the words you missed? (Enter 'y' to see, any other character to skip)\n");
        scanf("%s", command);
        if (strcmp(command, "y") == 0) {
            printMissed();
        }


        //Reset game
        freeBoggleBoard(board, size);
        memset(pointsArray, 0, size);

        //Ask to play again or end
        printf("Play again? (Enter any character to continue; Enter q to stop)\n");
        scanf("%s", command);
        system("clear");
    }

}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "game.h"

//Computer's possible words
static int wordIndex = -1;
static list* wordList;

// Calculate points per word
int calculateScore(char* word) {
    int length = strlen(word);
    int score = 0;
    if (length == 3 || length == 4) score = 1;
    if (length == 5) score = 2;
    if (length == 6) score = 3;
    if (length == 7) score = 5;
    if (length >= 8) score = 11;

    return score;
}

// Add word to list if it isn't already there
void checkInlist(char* userWord) {
    bool duplicate = false;
    for (int i = 0; i <= wordIndex; i++) {
        if (strcmp(userWord, wordList[i].word) == 0) {
            duplicate = true;
        }
    }
    if (duplicate == false) {
        wordIndex++;
        strcpy(wordList[wordIndex].word, userWord);
    }
}

// Return if letter searched is in the matrix range
bool inRange (boggleBoard** board, int size, int i, int j) {
    return (i >= 0 && i < size && j >= 0 && 
            j < size && !board[i][j].picked);
}

// Helper function to find all possible words
void computerFindWordsHelper(boggleBoard** board, int i, int j, int size, 
                char* userWord, int counter, trieNode* root) {
    // Select letter
    board[i][j].picked = true;
    // Add letter to string
    userWord[counter] = board[i][j].letter;
    // Handle Q
    if (userWord[counter] == 'q') {
        counter++;
        userWord[counter] = 'u';
    }
    counter++;
    // Check dictionary to validate prefix and print word to screen
    int searchCheck = searchTrie(root, userWord);
    // Valid word!
    if (strlen(userWord) >= 3 && searchCheck == 1) { 
        // Check for duplicates, add to list if new
        checkInlist(userWord);
    }

    // Outline of recursive loops sourced here:
    // https:// www.geeksforgeeks.org/boggle-find-possible-words-board-characters/
    // Modified to store words and pass other necessary variables

    // Recursively check adjacent letters to find words if userWord is prefix
    if (searchCheck != -1) {
        for (int row=i-1; row<=i+1; row++) {
            for (int col=j-1; col<=j+1; col++) {
                if (inRange(board, size, row, col)) {
                        computerFindWordsHelper(board, row, col, size, 
                        userWord, counter, root);
                }
            }
        }
    }

    // Handle Q
    if (userWord[counter-1] == 'q') {
        userWord[counter-2] = '\0';
    }
    // Get rid of current letter and unselect it
    userWord[counter-1] = '\0';

    board[i][j].picked = false;
}

// Computer finds all possible words on baord
void computerFindWords(boggleBoard** board, int size, trieNode* root) {
    // Reset index
    wordIndex = -1;

    // Allocate space for list of words
    // Assume max wordlist would be all the words in the dictionary
    // Assume 47 is largest word in dictionary
    wordList = (list*) malloc (sizeof(list) * 480000);
    for (int i = 0; i < 480000; i++) {
        wordList[i].word = (char*)malloc(47 * sizeof(char));
        wordList[i].playerFound = false;
        wordList[i].hidden = false;
    }
    // Hold index of current spot in userWord string
    int counter = 0;
    // Assume max size of word is longest word in dicitonary
    char userWord[47];
    
    // Find all possible words for every letter in the board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            memset(userWord, '\0', 47);
            counter = 0;
            computerFindWordsHelper(board, i, j, size, 
            userWord, counter, root);
        }
    }
    return;
}

// Check if the user-entered word is on the board
bool existsOnBoard(char* userInput) {
    bool check = false;
    for (int i = 0; i <= wordIndex; i++) {
        // If on the board
        if (strncmp(userInput, wordList[i].word, strlen(wordList[i].word)) == 0) {
            // Mark word in common
            wordList[i].playerFound = true;
            check = true;
        }
    }
    return check;
}

// Hide words computer found based on difficulty
void hideWords(int difficulty) {
    int level = 8 - difficulty;
    int tempIndex = wordIndex / level;

    // Hide certain word complexities
    for (int i = 0; i < wordIndex; i++) {
        if (difficulty == 1 && strlen(wordList[i].word) > 3)
            wordList[i].hidden = true;
        if (difficulty == 2 && strlen(wordList[i].word) > 4)
            wordList[i].hidden = true;
        if (difficulty == 3 && strlen(wordList[i].word) > 5)
            wordList[i].hidden = true;
    }
    // Hide random bunches of words
    for (int i = tempIndex; i < wordIndex; i++) {
        int randomWord = rand() % wordIndex;
        wordList[randomWord].hidden = true;
    }
}

// User enters words to play
int* userFindWords(boggleBoard** board, int size, 
                trieNode* root, int difficulty) {
    
    // Hide computer-found words based on difficulty
    hideWords(difficulty);
    
    printf("\n\nPLAYER 1: \n");

    // Assume max size of word would be longest word in dictionary
    char userInput[47];

    bool invalid = false;

    // Play for three minutes
    // https:// stackoverflow.com/questions/3930363/implement-time-delay-in-c
    unsigned int retTime = time(0) + 180;
    printf("Start finding words! You have three minutes! (Enter q to quit early) \n");
    scanf("%s", userInput);
    while (strcmp(userInput, "q") != 0) {
        for (int i = 0; i < strlen(userInput); i++) {
            // No invalid characters found yet
            if (!invalid) {
                if (!isalpha(userInput[i])) {
                    // Invalid characters found
                    printf("Invalid characters!\n");
                    invalid = true;
                }
                // Convert to lowercase
                userInput[i] = tolower(userInput[i]);
            }
        }
        // If no invalid characters
        if (!invalid) {
            // If word is not in the dictionary or not on the board
            if (!searchTrie(root, userInput) || !existsOnBoard(userInput))  {
                printf("Invalid word!\n");
            }
        }
        // Reset invalid character flag
        invalid = false;
        // Break if over time limit (user gets one more chance to check word)
        if (time(0) > retTime) break;
        scanf("%s", userInput);
    }

    printf("\n TIME'S UP! \n");

    // Player points @index 0; cpu points @index 1
    static int pointsArray[2];

    printf("\n");
    printf(".................................................................\n");
    printf("\nCOMPUTER FOUND:\n");
    int lw = 0;
    int flag = 0; // Line wrappers
    for (int i = 0; i < wordIndex; i++) {
        // X's mark words found in common (no points given)
        if (wordList[i].playerFound) {
            printf("X%sX\t", wordList[i].word);
            lw++;
            flag = 0;
        }
        // Print unique words, calculate score
        else if (!wordList[i].hidden && !wordList[i].playerFound) {
            printf("%s\t", wordList[i].word);
            pointsArray[1] += calculateScore(wordList[i].word);
            lw++;
            flag = 0;
        }
        // Control line wrappers
        if (lw % 20 == 0 && lw != 0 && flag == 0) {
            flag = 1;
            printf("\n");
        }
    }
    printf("\n.................................................................\n");

    printf("\n");
    printf("YOU FOUND:\n");
    lw = 0;
    for (int i= 0; i < wordIndex; i++) {
        // X's mark words found in common (no points given)
        if (wordList[i].playerFound && !wordList[i].hidden) {
            printf("X%sX\t", wordList[i].word);
            lw++;
            flag = 0;
        }
        // Print unique words, calculate score
        else if (wordList[i].playerFound) {
            printf("%s\t", wordList[i].word);
            pointsArray[0] += calculateScore(wordList[i].word);
            lw++;
            flag = 0;
        }
        // Control line wrappers
        if (lw % 20 == 0 && lw != 0 && flag == 0) {
            flag = 1;
            printf("\n");
        }
    }
    printf("\n.................................................................\n");

    return pointsArray;
}

// Free wordList memory
void freeWordlist() {
    for (int i = 0; i < 480000; i++) {
        free(wordList[i].word);
    }
    free(wordList);
}

// Print all the words user did not find 
void printMissed() {
    system("clear");
    printf(".................................................................\n");
    printf("WORDS YOU MISSED: \n");
    int lw = 0; // Line wrapper
    int flag = 0;
    for (int i = 0; i < wordIndex; i++) {
        if (!wordList[i].playerFound) {
            printf("%s\t", wordList[i].word);
            lw++;
           flag = 0;
        }
        if (lw % 10 == 0 && lw != 0 && flag == 0) {
            flag = 1;
            printf("\n");
        }
    }
    printf("\n.................................................................\n");

    // Free memory
    freeWordlist();
}

int main(void) {
    // Open dictionary file
    char word[1000];
    FILE *fp;
    
    // fp = fopen("/usr/share/dict/words", "r");
    fp = fopen("words_1.txt", "r");
    if (fp == NULL) {
        printf("Error: words file could not be found\n");
        return 1;
    }

    // Create root node
    struct trieNode* root = createTrieNode();

    // Invalid words include proper nouns and any non-alpha chars
    bool properNoun = false;
    bool invalid = false;

    // Read words file and construct trie
    while (fgets(word, 1000, fp) != NULL) {
        // Skip proper nouns
        if ((int)word[0] >= 65 && (int)word[0] <= 90) {
            properNoun = true;
        }
        if (!properNoun) {
            for (int i = 0; i < strlen(word); i++) {
                // Check for invalid characters
                if (!isalpha(word[i]) && word[i] != '\n' && word[i] != '\0') {
                    invalid = true;
                }
                // Get rid of new lines
                if (word[i] == '\n') {
                    word[i] = '\0';
                }
                // Convert all letters to lowercase
                word[i] = tolower(word[i]);
            }
            if (!invalid)
                insertTrieNode(root, word);
        }
        // Reset flags
        properNoun = false;
        invalid = false;
    }

    // Close file
    fclose(fp);

    system("clear");

    // GAME IMPLEMENTATION

    // Text art generated from http:// patorjk.com/software/taag/#p=display&h=1&v=1&f=Blocks&t=Boggle
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
    // Track total games score
    int playerScore = 0;
    int cpuScore = 0;
    char command[20];

    while(strcmp(command, "q") != 0) {
        // Prompt player for board size, halt on invalid input
        int size = promptBoardSize();

        // Prompt player for difficulty, halt on invalid input
        int difficulty = promptDifficulty();

        // Create and display board on screen
        system("clear");
        printf("-------WELCOME TO BOGGLE-------\n");

        boggleBoard** board = initializeBoard(size);
        displayBoard(size, board);

        // Computer: find all possible words on boggle board
        computerFindWords(board, size, root);

        // User: plays and finds words
        // Array holds player points, computer points
        int* pointsArray;

        pointsArray = userFindWords(board, size, root, difficulty);
        int playerPoints = pointsArray[0];
        int cpuPoints = pointsArray[1];

        // Print score totals

        printf("\nYou scored: %d points\n", playerPoints);
        printf("Computer scored: %d points\n\n", cpuPoints);
        printf(".................................................................\n");

        // Incrememnt winner's score, declare winner
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
        // Print standings
        printf("\n\nSTANDINGS:\n");
        printf("Player 1: %d \t Computer: %d\n\n", playerScore, cpuScore);
        printf(".................................................................\n");

        // Print words missed by user
        printf("See the words you missed? (Enter 'y' to see, any other character to skip)\n");
        scanf("%s", command);
        if (strcmp(command, "y") == 0) {
            printMissed();
        }

        // Reset game
        freeBoggleBoard(board, size);
        memset(pointsArray, 0, size);

        // Ask to play again or end
        printf("Play again? (Enter any character to continue; Enter q to stop)\n");
        scanf("%s", command);
        system("clear");
    }
    freeTrie(root);
}
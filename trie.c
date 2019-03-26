#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "game.h"

//Computer's possible words
static int wordIndex = -1;
static list* wordList;


//https://www.techiedelight.com/trie-implementation-insert-search-delete/
//Creates and returns a new trie node, initialized to NULLs
trieNode* createTrieNode() {
    trieNode* tNode = (struct trieNode*)malloc(sizeof(trieNode));
    tNode->isLeaf = false;
    for (int i = 0; i < 27; i++) {
        tNode->characters[i] = NULL;
    }
    return tNode;

}


//Inserts key into trie if it isn't already there
void insertTrieNode(trieNode* root, char* word) {
    trieNode* tCurrent = root;
    int index = 0;

    for (int i = 0; i < strlen(word); i++) {
        //Convert index of character into an integer
        index = word[i] - 'a';
        //If path does not exist, create a new node
        if (tCurrent->characters[index] == NULL) {
            tCurrent->characters[index] = createTrieNode();
        }
        //Move to the next node
        tCurrent = tCurrent->characters[index];
    }
    //End of word is marked as a leaf
    tCurrent->isLeaf = true;
    return;
}



int searchTrie(trieNode* root, char* word) {
    struct trieNode* tCurrent = root;
    int index;

    //Return false if the trie is empty
    if (root == NULL) 
        return -1;


    for (int i = 0; i < strlen(word); i++) {
        //Convert index of character into an integer
        index = word[i] - 'a';
        //If at the end of path and string isn't finished, invalid string
        if (tCurrent->characters[index] == NULL) {
            return -1;
        }
        //Move to the next node
        else {
            tCurrent = tCurrent->characters[index];
        }
        //Move to the next character
    }

    return (tCurrent->isLeaf);
}

//Free memory
void freeWordlist() {
    free(wordList);
}



//Calculate points per word
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


//Add word to list if it isn't already there
void checkInlist(char* userWord) {
    bool duplicate = false;
    for (int i = 0; i <= wordIndex; i++) {
        if (strncmp(userWord, wordList[i].word, strlen(userWord)) == 0) {
            duplicate = true;
        }
    }
    if (duplicate == false) {
        wordIndex++;
        strncpy(wordList[wordIndex].word, userWord, strlen(userWord));
    }
}


//Return if letter searched is in the matrix range
bool inRange (boggleBoard** board, int size, int i, int j) {
    return (i >= 0 && i < size && j >= 0 && 
            j < size && !board[i][j].picked);
}


//Helper function to find all possible words
void computerFindWordsHelper(boggleBoard** board, int i, int j, int size, 
                char* userWord, int counter, struct trieNode* tCurrent) {
    //Select letter
    board[i][j].picked = true;
    //Add letter to string
    userWord[counter] = board[i][j].letter;
    //Handle Q
    if (userWord[counter] == 'q') {
        counter++;
        userWord[counter] = 'u';
    }
    counter++;
    //Check dictionary to validate prefix and print word to screen
    int searchCheck = searchTrie(tCurrent, userWord);
    //Valid word
    if (strlen(userWord) >= 3 && searchCheck == 1) { 
        //Check for duplicates, add to list if new
        checkInlist(userWord);
    }

    //Recursively check adjacent letters to find words
    if (searchCheck != -1) {
        for (int row=i-1; row<=i+1; row++) {
            for (int col=j-1; col<=j+1; col++) {
                if (inRange(board, size, row, col)) {
                        computerFindWordsHelper(board, row, col, size, 
                        userWord, counter, tCurrent);
                }
            }
        }
    }

    //Handle Q
    if (userWord[counter-1] == 'q') {
        userWord[counter-2] = '\0';
    }
    //Get rid of current letter and unselect it
    userWord[counter-1] = '\0';

    board[i][j].picked = false;
    //printf("Userword garbage: %s\n", userWord);
}



//Computer finds all possible words on baord
void computerFindWords(boggleBoard** board, int size, struct trieNode* root) {
    //Reset index
    wordIndex = -1;

    //Allocate space for list of words
    //Assume max wordlist would be all the words in the dictionary
    wordList = (list*) malloc (480000 * sizeof(wordList));
    for (int i = 0; i < 48000; i++) {
        wordList[i].word = malloc(size*size*2 * sizeof(char));
        wordList[i].playerFound = false;
        wordList[i].hidden = false;
    }

    struct trieNode* tCurrent = root;
    //Hold index of current spot in userWord string
    int counter = 0;
    char userWord[size*size*2];
    
    //Find all possible words for every letter in the board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            memset(userWord, '\0', size*size*2);
            counter = 0;
            computerFindWordsHelper(board, i, j, size, 
            userWord, counter, tCurrent);
        }
    }

    return;

}


//Check if the user-entered word is on the board
bool existsOnBoard(char* userInput) {
    bool check = false;
    for (int i = 0; i <= wordIndex; i++) {
        //If on the board
        if (strncmp(userInput, wordList[i].word, strlen(userInput)) == 0) {
            //Mark word in common
            wordList[i].playerFound = true;
            check = true;
        }
    }
    return check;
}


//Hide words computer found based on difficulty
void hideWords(int difficulty) {
    int level = 8 - difficulty;
    int tempIndex = wordIndex / level;

    //Hide certain word complexities
    for (int i = 0; i < wordIndex; i++) {
        if (difficulty == 1 && strlen(wordList[i]. word) > 3)
            wordList[i].hidden = true;
        if (difficulty == 2 && strlen(wordList[i]. word) > 4)
            wordList[i].hidden = true;
        if (difficulty == 3 && strlen(wordList[i]. word) > 5)
            wordList[i].hidden = true;
    }
    
    //Hide random bunches of words
    for (int i = tempIndex; i < wordIndex; i++) {
        int randomWord = rand() % wordIndex;
        wordList[randomWord].hidden = true;
    }
}

//User enters words to play
int* userFindWords(boggleBoard** board, int size, 
                  struct trieNode* root, int difficulty) {
    
    //Hide computer-found words based on difficulty
    hideWords(difficulty);
    
    printf("\n\nPLAYER 1: \n");
    char userInput[1000];

    //Play for three minutes
    // /https://stackoverflow.com/questions/3930363/implement-time-delay-in-c
    unsigned int retTime = time(0) + 180;
    printf("Start finding words! You have three minutes! (Enter q to quit early) \n");
    scanf("%s", userInput);
    while (strncmp(userInput, "q", strlen(userInput)) != 0) {
        for (int i = 0; i < strlen(userInput); i++) {
            userInput[i] = tolower(userInput[i]);
        }
        //If word is not in the dictionary or not on the board
        if (!searchTrie(root, userInput) || !existsOnBoard(userInput))  {
            printf("Invalid word!\n");
        }
        if (time(0) > retTime) break;
        scanf("%s", userInput);
    }

    printf("\n TIME'S UP! \n");

    //Player points @index 0; cpu points @index 1
    static int pointsArray[2];

    printf("\n");
    printf(".................................................................\n");
    printf("\nCOMPUTER FOUND:\n");
    int lw = 0;
    int flag = 0; //Line wrappers
    for (int i = 0; i < wordIndex; i++) {
        if (wordList[i].playerFound) {
            printf("X%sX\t", wordList[i].word);
            lw++;
            flag = 0;
        }
        else if (!wordList[i].hidden && !wordList[i].playerFound) {
            printf("%s\t", wordList[i].word);
            pointsArray[1] += calculateScore(wordList[i].word);
            lw++;
            flag = 0;
        }
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
        if (wordList[i].playerFound && !wordList[i].hidden) {
            printf("X%sX\t", wordList[i].word);
            lw++;
            flag = 0;
        }
        else if (wordList[i].playerFound) {
            printf("%s\t", wordList[i].word);
            pointsArray[0] += calculateScore(wordList[i].word);
            lw++;
            flag = 0;
        }
        if (lw % 20 == 0 && lw != 0 && flag == 0) {
            flag = 1;
            printf("\n");
        }
    }
    printf("\n.................................................................\n");


    freeWordlist();
    
    return pointsArray;
}

void printMissed() {
    system("clear");
    printf(".................................................................\n");
    printf("WORDS YOU MISSED: \n");
    int lw = 0; //Line wrapper
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

}
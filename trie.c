#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "game.h"

//Computer's possible words
static int wordIndex = -1;
static char** wordList;

//https://www.techiedelight.com/trie-implementation-insert-search-delete/
//Creates and returns a new trie node, initialized to NULLs
struct trieNode* createTrieNode() {
    struct trieNode* tNode = (struct trieNode*)malloc(sizeof(struct trieNode));
    tNode->isLeaf = false;
    for (int i = 0; i < 26; i++) {
        tNode->characters[i] = NULL;
    }
    return tNode;

}


//Inserts key into trie if it isn't already there
void insertTrieNode(struct trieNode* root, char* word) {
    struct trieNode* tCurrent = root;
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
}



int searchTrie(struct trieNode* root, char* word) {
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
void freeWordList(int size) {
    for (int i = 0; i < size*size*2; i++) {
        free(wordList[i]);
    }
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
void checkInList(char* userWord) {
    bool duplicate = false;
    for (int i = 0; i <= wordIndex; i++) {
        if (strcmp(userWord, wordList[i]) == 0) {
            duplicate = true;
        }
    }
    if (duplicate == false) {
        wordIndex++;
        strcpy(wordList[wordIndex], userWord);
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
   // printf("%d---%s\n", size, userWord);
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
        printf("*%s\n", userWord);
        checkInList(userWord);
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
int computerFindWords(boggleBoard** board, int size, struct trieNode* root) {
    //Allocate space for list of words
    //Total possible words on a board of size n = 2^n
    //Longest length of word would be assuming a board full of Qu
    wordIndex = -1;

    wordList = (char**)malloc(480000 * sizeof(char *));
    for (int i = 0; i < size*size*2; i++) {
        wordList[i] = (char*)malloc(size*size*2 * sizeof(char));
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
            computerFindWordsHelper(board, i, j, size, userWord, counter, tCurrent);
        }
    }
    
    //Print word list to screen
    //Calculates score per word
    int score = 0;
    for (int i = 0; i <= wordIndex; i++) {
        score += calculateScore(wordList[i]);
        printf("%s\n", wordList[i]);
    }

    return score;

}


//Check if the user-entered word is on the board
bool existsOnBoard(char* userInput) {
    bool check = false;
    for (int i = 0; i <= wordIndex; i++) {
        if (strcmp(userInput, wordList[i]) == 0) {
            //add struct chosen element
            check = true;
        }
    }
    return check;
}


//User enters words to play
int userFindWords(boggleBoard** board, int size, struct trieNode* root) {
    printf("\n\nPLAYER 1: \n");
    int score = 0;
    char userInput[1000];
    printf("Enter word to check (q): \n");
    scanf("%s", userInput);
    for (int i = 0; i < strlen(userInput); i++) {
        userInput[i] = tolower(userInput[i]);
    }
    while (strcmp(userInput, "q") != 0) {
        if (searchTrie(root, userInput)) {//&& (existsOnBoard(userInput)))  {
            int points = calculateScore(userInput);
            printf("%d points!\n", points);
            score += points;
        }
    printf("Enter word to check (q to quit): \n");
    scanf("%s", userInput);
    }

    printf("\n\nwordIndex: %d\n\n", wordIndex);
    freeWordList(size);
    
    return score;
}
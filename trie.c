#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#include "game.h"

//Computer's possible words
int wordIndex = -1;
char** wordList;

//Creates and returns a new trie node, initialized to NULLs
struct trieNode* createTrieNode() {
    struct trieNode* tNode = NULL;
    tNode = (struct trieNode*)malloc(sizeof(struct trieNode));
    if (tNode) {
        tNode->isLeaf = false;
        for (int i = 0; i < 26; i++) {
            tNode->characters[i] = NULL;
        }
    }
    return tNode;

}


//Inserts key into trie if it isn't already there
void insertTrieNode(struct trieNode* *root, char* key) {
    struct trieNode* tCurrent = *root;
    int index = 0;

    while (*key) {
        //Convert index of character into an integer
        index = *key - 'a';
        //If path does not exist, create a new node
        if (tCurrent->characters[index] == NULL) {
            tCurrent->characters[index] = createTrieNode();
        }
        //Move to the next node
        tCurrent = tCurrent->characters[index];
        //Move to the next character
        key++;
    }
    tCurrent->isLeaf = true;
}



bool searchTrie(struct trieNode* root, char* key) {
    struct trieNode* tCurrent = root;
    int index;

    //Return false if the trie is empty
    if (root == NULL) 
        return false;

    while (*key) {
        //Convert index of character into an integer
        index = *key - 'a';
        //Move to the next node
        tCurrent = tCurrent->characters[index];
        //If at the end of path and string isn't finished, invalid string
        if (tCurrent == NULL)
            return false;
        //Move to the next character
        key++;
    }
    //If node is a leaf and end of string is reached, valid string
    return (tCurrent->isLeaf && tCurrent != NULL);
}


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
    if (searchTrie(tCurrent, userWord) && (strlen(userWord) >= 3)) {
        //Check for duplicates
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
    //Recursively check adjacent letters to find words
    for (int row=i-1; row>=0 && row<=i+1 && row<size; row++) {
        for (int col=j-1; col>= 0 && col<=j+1 && col<size; col++) {
            if (board[row][col].picked == false) {
                computerFindWordsHelper(board, row, col, size, userWord, counter, tCurrent);
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
}



void computerFindWords(boggleBoard** board, int size, struct trieNode* root) {
    //Allocate space for list of words
    //Total possible words on a board of size n = 2^n
    //Longest length of word would be assuming a board full of Qu
    wordList = (char**)malloc(pow(2, size) * sizeof(char *));
    for (int i = 0; i < 1000; i++) {
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

    printf("SCORE: %d\n", score);

}


bool existsOnBoard(char* userInput) {
    bool check = false;
    for (int i = 0; i <= wordIndex; i++) {
        if (strcmp(userInput, wordList[i]) == 0) {
            check = true;
        }
    }
    return check;
}



void userFindWords(boggleBoard** board, int size, struct trieNode* root) {
    printf("\n\nPLAYER 1: \n");
    int score = 0;
    char userInput[1000];
    printf("Enter word to check (q): \n");
    scanf("%s", userInput);
    for (int i = 0; i < strlen(userInput); i++) {
        userInput[i] = tolower(userInput[i]);
    }
    while (strcmp(userInput, "q") != 0) {
        if (searchTrie(root, userInput) && (existsOnBoard(userInput)))  {
            printf(">>>%s exists!\n", userInput);
            score += calculateScore(userInput);
        }
        else {
            printf(">>>%s does not exist\n", userInput);
        }
    printf("Enter word to check (q to quit): \n");
    scanf("%s", userInput);
    }

    printf("SCORE: %d\n", score);
}

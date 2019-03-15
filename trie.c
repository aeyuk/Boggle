#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "game.h"

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


void findWordsUtil(boggleBoard** board, int i, int j, int size, char* userWord, int counter, struct trieNode* tCurrent) {
    board[i][j].picked = true;
    userWord[counter] = board[i][j].letter;
    if (userWord[counter] == 'q') {
        counter++;
        userWord[counter] = 'u';
    }
    counter++;
    if (searchTrie(tCurrent, userWord))
        printf("%s exists\n", userWord);
    //else printf("%s does not exist\n", userWord);
    for (int row=i-1; row<=i+1 && row<size; row++)
        for (int col=j-1; col<=j+1 && col<size; col++)
            if (row>=0 && col>=0 && board[row][col].picked == false)
                findWordsUtil(board, row, col, size, userWord, counter, tCurrent);

    if (userWord[counter] == 'q') {
        userWord[counter-2] = '\0';
    }
    userWord[counter-1] = '\0';
    board[i][j].picked = false;
}


void findWords(boggleBoard** board, int size, struct trieNode* root) {
    struct trieNode* tCurrent = root;
    int counter = 0;
    char userWord[size*size*2];
    memset(userWord, '\0', size*size*2);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            findWordsUtil(board, i, j, size, userWord, counter, tCurrent);
        }
    }
}


/*
void userFindWords(struct trieNode* root) {
    char input[1000];
    printf("Enter word to check (q): \n");
    scanf("%s", input);
    for (int i = 0; i < strlen(input); i++) {
        input[i] = tolower(input[i]);
    }
    while (strcmp(input, "q") != 0) {
        if (searchTrie(root, input)) {
            printf(">>>%s exists!\n", input);
        }
        else {
            printf(">>>%s does not exist\n", input);
        }
    printf("Enter word to check (q to quit): \n");
    scanf("%s", input);
    }
}
*/
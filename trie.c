#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "game.h"

// https://www.techiedelight.com/trie-implementation-insert-search-delete/
// General trie implementation sourced and modified
// Creates and returns a new trie node, initialized to NULLs
trieNode* createTrieNode() {
    trieNode* tNode = (trieNode*)malloc(sizeof(trieNode));
    tNode->isLeaf = false;
    for (int i = 0; i < 26; i++) {
        tNode->characters[i] = NULL;
    }
    return tNode;
}

// Inserts key into trie if it isn't already there
void insertTrieNode(trieNode* root, char* word) {
    trieNode* tCurrent = root;
    int index = 0;

    for (int i = 0; i < strlen(word); i++) {
        // Convert index of character into an integer
        index = word[i] - 'a';
        // If path does not exist, create a new node
        if (tCurrent->characters[index] == NULL) {
            tCurrent->characters[index] = createTrieNode();
        }
        // Move to the next node
        tCurrent = tCurrent->characters[index];
    }
    // End of word is marked as a leaf
    tCurrent->isLeaf = true;
    return;
}

int searchTrie(trieNode* root, char* word) {
    trieNode* tCurrent = root;
    int index;

    // Return false if the trie is empty
    if (root == NULL) 
        return -1;

    for (int i = 0; i < strlen(word); i++) {
        // Convert index of character into an integer
        index = word[i] - 'a';
        // If at the end of path and string isn't finished, invalid string
        if (tCurrent->characters[index] == NULL) {
            return -1;
        }
        // Move to the next node
        else {
            tCurrent = tCurrent->characters[index];
        }
    }
    return (tCurrent->isLeaf);
}

void freeNode(trieNode* tCurrent) {
    for (int i = 0; i < 26; i++) {
        if (tCurrent->characters[i] != NULL) {
            freeNode(tCurrent->characters[i]);
        }
    }
    free(tCurrent);
}

// Free trie memory
void freeTrie(trieNode* root) {
    if (root != NULL) {
        trieNode* tCurrent = root;
        freeNode(tCurrent);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Trie node struct
struct trieNode {
    struct trieNode *childrenNodes[26]; 
    bool end;                       //if true, node = end of word
};


//Creates and returns a new trie node, initialized to NULLs
struct trieNode* createNewNode() {
    struct trieNode* tNode = NULL;
    tNode = (struct trieNode*)malloc(sizeof(struct trieNode));
    if (tNode) {
        tNode->end = false;
        for (int i = 0; i < 26; i++) {
            tNode->childrenNodes[i] = NULL;
        }
    }
    return tNode;

}

//Inserts key into trie if it isn't already there
void insertNode(struct trieNode* root, char* key) {
    int index;
    struct trieNode* tCurrent = root;

    //Traverse through letters of word
    for (int i = 0; i < strlen(key); i++) {
        //Store index of key as an int
        index = (int)key[i] - (int)'a';
        if (!tCurrent->childrenNodes[index]) {
            //Makes new node if it doesn't exist
            tCurrent->childrenNodes[index] = createNewNode();
        }
        //Step to node's children
        tCurrent = tCurrent->childrenNodes[index];
    }
    //Mark end of word for the leaf node
    tCurrent->end = true;
}

bool searchTrie(struct trieNode* root, char* key) {
    int index;
    struct trieNode* tCurrent = root;

    //Traverse through letters of word
    for (int i = 0; i < strlen(key); i++) {
        //Convert key to character index
        index = (int)key[i] - (int)'a';
        if (!tCurrent->childrenNodes[index]) {
            return false;
        }
        //Step to node's children
        tCurrent = tCurrent->childrenNodes[index];
    }
    //Returns true if node exists and is the end of word
    return (tCurrent != NULL && tCurrent->end);
}


int main(void) {
    char word[1000];

    FILE *fp;
    fp = fopen("/usr/share/dict/words", "r");
    if (fp == NULL) {
        printf("Error: words file could not be found\n");
        return 1;
    }

    //Create root node
    struct trieNode* root = createNewNode();

    //Read words file and construct trie
    while (fgets(word, 1000, fp) != NULL) {
        for (int i = 0; i < strlen(word); i++) {
            //Convert all letters to lowercase
            word[i] = tolower(word[i]);
        }
        insertNode(root, word);
    }

    printf("checking the word hello\n");
    if (searchTrie(root, "hello"))
        printf("hello exists\n");
    else printf("hello does not exist\n");

    fclose(fp);

    return 0;
}
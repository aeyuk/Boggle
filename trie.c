#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Trie node struct
struct trieNode {
    struct trieNode *characters[26]; 
    bool isLeaf;                       //if true, node = isLeaf of word
};


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


int main(void) {
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

    char input[1000];
    printf("Enter word to check (q): \n");
    scanf("%s", input);
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

    fclose(fp);

    return 0;
}
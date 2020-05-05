#include "board.h"

//Computer's possible words
static int wordIndex = -1;

static list* wordList;

typedef struct trieNode {
    struct trieNode *characters[26]; 
    bool isLeaf;
} trieNode;

trieNode* createTrieNode();

void insertTrieNode(trieNode* root, char* key);

int searchTrie(trieNode* root, char* key);

void freeWordList();

void freeNode(trieNode* tCurrent);

void freeTrie(trieNode* root);
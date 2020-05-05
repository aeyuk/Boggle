#include "trie.h"

//Word List
typedef struct list {
     char* word;
     bool playerFound;
     bool hidden;
} list;

int calculateScore(char* word);

void checkInList(char* userWord);

bool inRange (boggleBoard** board, int size, int i, int j);

void computerFindWordsHelper(boggleBoard** board, int i, int j, int size, char* userWord, 
                            int counter, trieNode* root);

void computerFindWords(boggleBoard** board, int size, trieNode* root);

bool existsOnBoard(char* userInput);

void hideWords(int difficulty);

int* userFindWords(boggleBoard** board, int size, trieNode* root, int difficulty);

void printMissed();
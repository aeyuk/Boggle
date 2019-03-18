#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "game.h"

int main(void) {

    //Open dictionary file
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

    //Close file
    fclose(fp);


    //Prompt player for board size
    int size = 0;
    printf("Enter size: \n");
    scanf("%d", &size);

    //Create and display board on screen
    boggleBoard** board = initializeBoard(size);
    displayBoard(size, board);

    //Computer: find all possible words on boggle board
    printf("Computer:\n");
    computerFindWords(board, size, root);

    //User inputs all found words
    //TODO: make sure words come FROM THE BOARD
    userFindWords(board, size, root);
}


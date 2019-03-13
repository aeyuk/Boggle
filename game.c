#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "game.h"

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


    int size = 0;
    printf("Enter size: \n");
    scanf("%d", &size);

    boggleBoard** board = initializeBoard(size);
    displayBoard(size, board);

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
}


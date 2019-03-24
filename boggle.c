#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>

#include "game.h"



WINDOW *create_newwin(int height, int width, int starty, int startx);

int main(void) {
    //Open dictionary file
    char word[1000];
    FILE *fp;
    //fp = fopen("words_alpha.txt", "r");
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
        insertTrieNode(root, word);
    }

    //Close file
    fclose(fp);




	int ch;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	printw("WELCOME TO BOGGLE\n");
    printw("Press F1 to exit\n");
	refresh();
    WINDOW *board, *score, *input;
	board = create_newwin(LINES/2, COLS/3, 0, 0);
    score = create_newwin((LINES / 2), (2*COLS / 3), 0, COLS/3);
    input = create_newwin((LINES / 2), COLS-1, LINES/2, 0);

    wmove(input, 1, 1);
    //Prompt player for board size, halt on invalid input
    int size = promptBoardSize();
    size = size +10;
    wrefresh(input);
    //wclear(input);

    //Prompt player for difficulty, halt on invalid input
    int difficulty = promptDifficulty();
    difficulty = difficulty + 10;
    wrefresh(input);
    //wclear(input);

	while((ch = getch()) != KEY_F(1))
	{	
	}
		
	endwin(); //End curses mode
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win); //Show box

	return local_win;
}
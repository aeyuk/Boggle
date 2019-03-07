#define WINDOW_WIDTH 30
#define WINDOW_HEIGHT 60

#include <curses.h>
#undef OK
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

//Refresh page when alarm is reached
int catchAlarm(int sig) {
    if (sig == SIGALRM) {
        clear();
        refresh();
        endwin();
        printf("Ending one child: %d\n", getpid());
        _exit(1);
    }
    return sig;
}

void displayInterface(char *words, int id) {
    
    WINDOW *boggleWindow;
    int yOffset;

    //Set up the ncurses
    initscr();              // Initialize the curses library
    refresh();
    keypad(stdscr, TRUE);   // Enable keyboard mapping
    nonl();                 // Make sure curses can detect return key
    scrollok(stdscr, TRUE); // Window is scrolled up one line
    move (0, 0);            //Set cursor location

    //Set up the window
    yOffset = (LINES - WINDOW_HEIGHT) / 2;
    boggleWindow = newwin(WINDOW_WIDTH, WINDOW_HEIGHT, yOffset, 0);
    box(boggleWindow, 0 , 0);
    wrefresh(boggleWindow);
    refresh();


    //Set an alarm
    signal(SIGALRM, (sig_t)catchAlarm);
    alarm(10); //Alarm goes off every three minutes


    //Set cursor location
    move(5, 1);
    printw("Welcome to Boggle Bitches");
    refresh();


    getch();
    cbreak();
    delwin(boggleWindow);
    endwin();

}

int main(void) {
    char words[5];

    displayInterface(words, 5);

    return 0;
}

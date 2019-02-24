#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>


//Refresh page when alarm is reached
void catchAlarm (int sig) {
  if ( sig == SIGALRM ) {
    clear();
    refresh();
    endwin();
    printf("Ending one child: %d\n", getpid());
    _exit(1);
  }
}

void displayInterface(char* words, int id) {

  //Set up the ncurses
  (void) initscr();         // Initialize the curses library
  keypad(stdscr, TRUE);     // Enable keyboard mapping
  nonl();                   // Make sure curses can detect return key
  echo();                   // Do not echo input 
  scrollok(stdscr, TRUE);    // Window is scrolled up one line

  //Set an alarm
  signal (SIGALRM, (sig_t)catchAlarm);
  alarm(180);               //Alarm goes off every three minutes

  //Set cursor location
  move(0, 0);
  printw("-------------------------");
  refresh();
  printw("Welcome to Boggle Bitches");
  refresh();
  printw("-------------------------");
  refresh();



}

int main(void) {
char words[5];

displayInterface(words, 5);

return 0;
}
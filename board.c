//Specific dice configuration for English Boggle (16 dice)
#define A "rifobx"
#define B "ifehey"
#define C "denows"
#define D "utoknd"
#define E "hmsrao"
#define F "lupets"
#define G "acitoa"
#define H "ylgkue"
#define I "qbmjoa"
#define J "ehispn"
#define K "vetign"
#define L "baliyt"
#define M "exavnd"
#define N "ralesc"
#define O "uwilrg"
#define P "pacemd"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Return available cube
char selectDice(char* diceList, int randomDice) {
    printf("2 check selectDice\n");
    char temp;
    while (diceList[randomDice] == '\0') {              //Find an available cube
        randomDice++;
        if (randomDice == 16) {                         //Reset to beginning of the list
            randomDice = 0;
        }
    }

    temp = diceList[randomDice];                        //Store selected cube
    diceList[randomDice] = '\0';                        //Set used cubes to null
    return temp;                                        //Return selected cube
}

//Return the possible letters corresponding to the die
char* getCubeLetters(char cube) {
        printf("4 check getCubeLetters\n");
        printf("%c\n", cube);

    if (cube == 'A') return A;
    else if (cube == 'B') return B;
    else if (cube == 'C') return C;
    else if (cube == 'D') return D;
    else if (cube == 'E') return E;
    else if (cube == 'F') return F;
    else if (cube == 'G') return G;
    else if (cube == 'H') return H;
    else if (cube == 'I') return I;
    else if (cube == 'J') return J;
    else if (cube == 'K') return K;
    else if (cube == 'L') return L;
    else if (cube == 'M') return M;
    else if (cube == 'N') return N;
    else if (cube == 'O') return O;
    else return P;
}


//Get random letter from one of six cube sides
char getDiceLetter(char cube) {
        printf("3 check getDiceLetter\n");
    char letters[7] = "000000";
    strncpy(letters, getCubeLetters(cube), 6);
    printf("letters: %s\n", letters);
    int randNum = rand() % strlen(letters);
    return letters[randNum];
}



typedef struct boggleBoard {
    char letter; //Holds cube's face value
    int flag;
} boggleBoard;

//Initialize the 4x4 board
boggleBoard** initializeBoard() {
        printf("1 check initializeBoard\n");

    
    //Hold all die in an array
    char diceList[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                     'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};

    //Allocate space for the 4x4 board
    boggleBoard** board = (boggleBoard**) malloc (4 * sizeof(boggleBoard*));
    for (int i = 0; i < 4; i++) {
        board[i] = (boggleBoard*) malloc (sizeof (boggleBoard) * 4);
    }

    //Randomly pick a dice; remove it from the list
    int randomDice = 0;
    char cube;
    for (int i = 0; i < 4; i++) {                        //Board rows
        for (int j = 0; j < 4; j++) {                    //Board cols
            randomDice = rand() % strlen(diceList);      //Get a random dice
            cube = selectDice(diceList, randomDice);     //Remove the dice from the possible options
            board[i][j].letter = getDiceLetter(cube);           //Get a letter from the dice side
            printf("Board run %d\n", j);
        }
    }

    return board;
}

int main(void) {
        printf("0 check main\n");

    boggleBoard** board = initializeBoard();
    for (int i = 0; i < 4; i++) {
        printf("hellooo\n");
        for (int j = 0; j < 4; j++) {
            printf("%c", board[i][j].letter);
        }
    }
    
    return 0;
}


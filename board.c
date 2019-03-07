//Specific dice configuration for English Boggle (16 dice)
#define A "qbzjxk"
#define B "hhlrdo"
#define C "telpci"
#define D "ttotem"
#define E "aeaeee"
#define F "touoto"
#define G "nhdtho"
#define H "ssnseu"
#define I "sctiep"
#define J "yifpsr"
#define K "ovwrgr"
#define L "lhnrod"
#define M "riyprh"
#define N "eandnn"
#define O "eeeema"
#define P "aaafsr"
#define Q "afaisr"
#define R "dordln"
#define S "mnneag"
#define T "ititie"
#define U "aumeeg"
#define V "yifasr"
#define W "ccwnst"
#define X "uotwon"
#define Y "etilic"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Return available cube
char selectDice(char* diceList, int randomDice) {
    printf("2 check selectDice\n");
    char temp;
    while (diceList[randomDice] == '!') {              //Find an available cube
        randomDice++;
        if (randomDice == 25) {                         //Reset to beginning of the list
            randomDice = 0;
        }
    }

    temp = diceList[randomDice];                        //Store selected cube
    diceList[randomDice] = '!';                        //Set used cubes to null
    return temp;                                        //Return selected cube
}

//Return the possible letters corresponding to the die
char* getCubeLetters(char cube) {
        printf("5 check getCubeLetters\n");
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
    else if (cube == 'P') return P;
    else if (cube == 'Q') return Q;
    else if (cube == 'R') return R;
    else if (cube == 'S') return S;
    else if (cube == 'T') return T;
    else if (cube == 'U') return U;
    else if (cube == 'V') return V;
    else if (cube == 'W') return W;
    else if (cube == 'X') return X;
    else return Y;
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

//Initialize the 5x5 board
boggleBoard** initializeBoard() {
        printf("1 check initializeBoard\n");

    
    //Hold all die in an array
    char diceList[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'
    };

    //Allocate space for the 5x5 board
    boggleBoard** board = (boggleBoard**) malloc (5 * sizeof(boggleBoard*));
    for (int i = 0; i < 5; i++) {
        board[i] = (boggleBoard*) malloc (sizeof (boggleBoard) * 5);
    }

    //Randomly pick a dice; remove it from the list
    int randomDice = 0;
    char cube;
    for (int i = 0; i < 5; i++) {                        //Board rows
        for (int j = 0; j < 5; j++) {                    //Board cols
            printf("Board run %d\n", j);
            randomDice = rand() % strlen(diceList);      //Get a random dice
            cube = selectDice(diceList, randomDice);     //Remove the dice from the possible options
            board[i][j].letter = getDiceLetter(cube);           //Get a letter from the dice side
        }
    }

    return board;
}

int main(void) {
        printf("0 check main\n");

    boggleBoard** board = initializeBoard();
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c", board[i][j].letter);
        }
        printf("\n");
    }
    
    return 0;
}


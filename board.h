typedef struct boggleBoard {
    char letter;
    bool picked;
} boggleBoard;

int checkInput(char* input, char* type);

int promptBoardSize();

int promptDifficulty();

void freeBoggleBoard(boggleBoard** board, int size);

boggleBoard** initializeBoard(int size);

void displayBoard(int size, boggleBoard** board);

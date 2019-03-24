typedef struct boggleBoard {
    char letter;
    bool picked;
} boggleBoard;
int promptBoardSize();
int checkInput(char* size, char* type);
int promptDifficulty();
int checkDifficulty(int difficulty);
void delay(int numSeconds);
boggleBoard** initializeBoard(int size);
void freeBoggleBoard(boggleBoard** board, int size);
void displayBoard(int size, boggleBoard** board);

typedef struct trieNode {
    struct trieNode *characters[26]; 
    bool isLeaf;
} trieNode;
trieNode* createTrieNode();
void insertTrieNode(struct trieNode* root, char* key);
int searchTrie(struct trieNode* root, char* key);

typedef struct list {
     char* word;
     bool playerFound;
     bool hidden;
} list;
void freeWordList();
int calculateScore(char* word);
void checkInList(char* userWord);
bool inRange (boggleBoard** board, int size, int i, int j);
void computerFindWordsHelper(boggleBoard** board, int i, int j, int size, char* userWord, 
                            int counter, struct trieNode* root);
void computerFindWords(boggleBoard** board, int size, struct trieNode* root);
bool existsOnBoard(char* userInput);
void hideWords(int difficulty);
int* userFindWords(boggleBoard** board, int size, struct trieNode* root, int difficulty);
void printMissed();
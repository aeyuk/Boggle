//Board
typedef struct boggleBoard {
    char letter;
    bool picked;
} boggleBoard;
int promptBoardSize();
int checkInput(char* size, char* type);
int promptDifficulty();
int checkDifficulty(int difficulty);
boggleBoard** initializeBoard(int size);
void freeBoggleBoard(boggleBoard** board, int size);
void displayBoard(int size, boggleBoard** board);

//Trie
typedef struct trieNode {
    struct trieNode *characters[27]; 
    bool isLeaf;
} trieNode;
trieNode* createTrieNode();
void insertTrieNode(trieNode* root, char* key);
int searchTrie(trieNode* root, char* key);

//Word List
typedef struct list {
     char* word;
     bool playerFound;
     bool hidden;
} list;
void freeWordList();
void freeNode(trieNode* tCurrent);
void freeTrie(trieNode* root);
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
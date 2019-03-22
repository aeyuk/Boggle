typedef struct boggleBoard {
    char letter;
    bool picked;
} boggleBoard;

int checkSize(char* size);

void delay(int numSeconds);

boggleBoard** initializeBoard(int size);

void freeBoggleBoard(boggleBoard** board, int size);

void displayBoard(int size, boggleBoard** board);

struct trieNode {
    struct trieNode *characters[26]; 
    bool isLeaf;
};

// typedef struct wordList {
//     char* word;
//     bool playerFound;
// } wordList;

struct trieNode* createTrieNode();

void insertTrieNode(struct trieNode* *root, char* key);

int searchTrie(struct trieNode* root, char* key);

void freeWordList(int size);

int calculateScore(char* word);

void checkInList(char* userWord);

bool inRange (boggleBoard** board, int size, int i, int j);

void computerFindWordsHelper(boggleBoard** board, int i, int j, int size, char* userWord, 
                            int counter, struct trieNode* root);

int computerFindWords(boggleBoard** board, int size, struct trieNode* root);

int userFindWords(boggleBoard** board, int size, struct trieNode* root);
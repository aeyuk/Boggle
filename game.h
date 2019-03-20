typedef struct boggleBoard {
    char letter;
    bool picked;
} boggleBoard;

int checkSize(char* size);

void delay(int numSeconds);

boggleBoard** initializeBoard(int size);

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

bool searchTrie(struct trieNode* root, char* key);

int calculateScore(char* word);

void computerFindWordsHelper(boggleBoard** board, int i, int j, int size, char* userWord, 
                            int counter, struct trieNode* root);

int computerFindWords(boggleBoard** board, int size, struct trieNode* root);

int userFindWords(boggleBoard** board, int size, struct trieNode* root);
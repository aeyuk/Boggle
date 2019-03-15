typedef struct boggleBoard {
    char letter;
    int picked;
} boggleBoard;

boggleBoard** initializeBoard(int size);

void displayBoard(int size, boggleBoard** board);


struct trieNode {
    struct trieNode *characters[26]; 
    bool isLeaf;
};

struct trieNode* createTrieNode();

void insertTrieNode(struct trieNode* *root, char* key);

bool searchTrie(struct trieNode* root, char* key);

void findWordsUtil(boggleBoard** board, int i, int j, int size, char* userWord, int counter, struct trieNode* root);

void findWords(boggleBoard** board, int size, struct trieNode* root);

//void userFindWords(struct trieNode* root);


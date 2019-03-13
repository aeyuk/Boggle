typedef struct boggleBoard {
    char letter;
    int flag;
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

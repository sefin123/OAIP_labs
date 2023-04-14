#define MAXWORD 256


typedef struct binaryTree {
	int data;
	//char *word;
	struct Tree *left;
	struct Tree *right;
}binaryTree;



void Print(binaryTree* tree);


binaryTree* insert(binaryTree* root, int data);


binaryTree* createNode(int data);


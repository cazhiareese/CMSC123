#include <stdio.h>
#include <stdlib.h>
typedef struct tree_node{
    struct tree_node* leftChild;  
    struct tree_node* rightSibling; 
    int key;    //value of the node
    int height; //height of the node
    int childCount;
} TREE_NODE;

typedef struct tree{
    TREE_NODE* root; //root pointer
    int maxSize;    //number of maximum nodes in the tree
    int size;   //current size of the tree
    int maxChild;
}TREE;


TREE *createTree(int n, int max)
{
    TREE *newTree = (TREE *) malloc(sizeof(TREE));
    newTree -> root = NULL;
    newTree -> size = 0;
    newTree -> maxSize = max;
    newTree -> maxChild = n;

    return newTree;
}

TREE_NODE *createNode(int key)
{
    TREE_NODE *new = (TREE_NODE *) malloc(sizeof(TREE_NODE));
    new -> leftChild = NULL;
    new -> rightSibling = NULL;
    new -> key = key;
    new -> height = 0;
    new -> childCount = 0;

    return new;
}


void insert(TREE *T, TREE_NODE *node)
{
    
}
int main()
{

    char command;
	int key, result;

    TREE *T = createTree(3, 100);
    TREE_NODE *node;
    while (1)
    {
        scanf(" %c", &command);
        switch(command)
        {
            case '+':
                scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				insert(T, createNode(key));
				break;
            case '?':
				scanf("%d", &key);
				printf("Searching node with key: %d. Location: %p\n", key, search(T, key));
				// (nil) means NULL pointer
				break;
            case 'p':
                // print code
                print(T);
                break;
            default:
				printf("Unknown command: %c\n", command);
        }

        return 0;
    }
}


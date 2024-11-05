#include <stdio.h>
#include <stdlib.h>
typedef struct tree_node{
    struct bst_node* leftChild;  
    struct bst_node* rightSibling; 
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


TREE *createTree(int n)
{

}
int main()
{
    TREE *T = createTree(3);

    while (1)
    {

    }
}


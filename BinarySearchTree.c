#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int data;
    struct node *parent;
    struct node *left;
    struct node *right;
} NODE; 

typedef struct btree
{
    NODE *root;
} TREE;

TREE *createTree ()
{
    TREE *tree = (TREE *) malloc(sizeof(TREE));
    tree -> root = NULL;

    return tree;
}

NODE *createNew(int value)
{
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new -> data = value;
    new-> parent = NULL;
    new -> left = NULL;
    new-> right = NULL;

    return new;
}

NODE *search ()
{

}


void insertIterative (TREE *bt, NODE *node)
{
    if ((bt -> root) == NULL)
    {
        bt->root = node;
        
    }else{
        //Insertion
        NODE *temp = bt->root;
        NODE *p2 = NULL;
        while (temp != NULL)
        {
            p2 = temp;
            if (node ->data > temp ->data)
            {
                temp = temp -> right;
            }else{
                temp = temp -> left;
            }
        }

        
        if (node -> data > p2-> data)
        {
            p2 -> right = node;
        }else
        {
            p2 -> left = node;
        }
        node -> parent = p2; 

    }
}



void printTraversal (TREE *bt)
{
    NODE *temp = bt->root;

    while(temp != NULL){
        printf("\ncurrent node: %d ", temp->data);
        if (temp->right!= NULL)
            printf("\nright child: %d", temp->right->data);

        if (temp->left!= NULL)
            printf("\nleft child: %d", temp->left->data);

        temp = temp->right;
    }

}


int main ()
{
    TREE *tree = createTree();

    while (1)
    {
        int scan;
        printf("\nInsert: ");
        scanf("%d", &scan);
        NODE *new = createNew(scan);
        insertIterative(tree, new);
        printTraversal(tree);

    }
    return 0;
}


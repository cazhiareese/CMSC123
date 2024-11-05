/* ********************************************************* *
 * template.c                                                *
 *                                                           *
 * Template C Source File for AVL Insert.                    *
 *                                                           *
 * !!! DO NOT EDIT THE CONTENTS OF THE MAIN FUNCTION !!!     *
 *                                                           *
 * ********************************************************* */
#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

AVL_NODE * createAVLNode(int key){
    return createBSTNode(key, NULL, NULL, NULL);
}

AVL * createAVL(int max){
    return createBST(max);
}

/**** PUT YOUR FUNCTIONS HERE ******************************/
void leftRotate(AVL* A, AVL_NODE * node){
	//leftRotate's pivot is always the right child of the critical node
	AVL_NODE *pivot = node -> right;
	//pass left child of pivot as right child of critical
	node -> right = pivot -> left;
	if(node -> right != NULL)
		node -> right -> parent = node;
	
	//make pivot's parent pointer point to critical's parent
	//pivot takes critical's place
	pivot -> parent = node -> parent;
	if (node -> parent == NULL)
	{
		A-> root = pivot;
	}else{
		if (node -> parent -> right == node)
		
			node -> parent -> right = pivot;
		else node -> parent -> left = pivot;
	}
	//critical is left child of pivot
	pivot -> left = node;
	//adjust parent pointer 
	node -> parent = pivot;
	//updateHeight from critical
	updateHeight(node);

}
void rightRotate(AVL* A, AVL_NODE * node){
	//rightRotate's pivot is always the left child of the critical node
	AVL_NODE *pivot = node -> left;
	//pass right child of pivot as left child of critical
	node -> left = pivot -> right;
	if(node -> left != NULL)
		node -> left -> parent = node;
	
	//make pivot's parent pointer point to critical's parent
	//pivot takes critical's place
	pivot -> parent = node -> parent;
	if (node -> parent == NULL)
	{
		A-> root = pivot;
	}else{
		if (node -> parent -> right == node)
		
			node -> parent -> right = pivot;
		else node -> parent -> left = pivot;
	}
	
	//critical is right child of pivot
	pivot -> right = node;
	//adjust parent pointer
	node -> parent = pivot;
	//adjust height from critical
	updateHeight(node);
}

//checkbalance of the children of node
//-1 is returned if NULL (from heightOf)
int checkBalance (AVL_NODE *node){
	int leftHeight = heightOf(node->left);
	int rightHeight = heightOf(node -> right);
	return leftHeight - rightHeight;
}

//AVL Insert
void AVLInsert(AVL* A, AVL_NODE* node){
	//BST Insert
	insert(A, node);

	//initialize critical, parent, and pivot node
	AVL_NODE *critical = node -> parent;
	AVL_NODE *parent = NULL, *pivot = node;
	while (critical != NULL)
	{
		//store critical's parent
		parent = critical -> parent;
		//check balance of critical node
		int criticalBalance = checkBalance(critical);
		int pivotBalance;

		//if >1 the left child has a higher height than that of the right
		//if <-1 the right child has a higher height than that of the left
		//both causes imbalance in the AVL tree
		if (criticalBalance > 1)
		{
			//left leaning, pivot is automatically the left child
			pivot = critical -> left;
			pivotBalance = checkBalance(pivot);
			if (pivotBalance < 0)
				//left right leaning
				leftRotate(A, pivot);
			rightRotate(A, critical);	
		}else if(criticalBalance < -1)
		{
			//right leaning, pivot is automatically the right child
			pivot = critical -> right;
			pivotBalance = checkBalance(pivot);
			if(pivotBalance > 0)
				//right left leaning
				rightRotate(A, pivot);
			leftRotate(A, critical);
		}

		critical = parent;
	}

}


int heightOf(AVL_NODE * node){
	//return -1 if NULL
	if(node == NULL) return -1;
	//return actual node height
	return node -> height;
}



/**** FUNCTIONS ABOVE **************************************/

int main(){

	char command;
	int key, result;

	AVL *A = createAVL(100);
	AVL_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				AVLInsert(A, createAVLNode(key));
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(A);
				printf("\n");
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(A);
				break;
			case 'Q':
				clear(A);
				free(A);
				return 0;
            default:
                printf("Unknown command %c\n", command);
       }
    }
}

/* ********************************************************* *
 * BST.c                                                     *
 *                                                           *
 * Contains the function definitions of all functions        *
 *    declared in BST.h.                                     *
 *                                                           *
 * !!! DO NOT EDIT LINES 11-28 !!!                           *
 *                                                           *
 * ********************************************************* */
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

// a recursive subroutine to display the BST in tree mode
void showTreeHelper(BST_NODE* node, int tabs){

	if(!node) return; // node is null, do nothing
	showTreeHelper(node->right, tabs + 1);
	for(int i=0; i<tabs; i++) printf("\t");
	printf("%d(%d)\n", node->key, node->height);
	showTreeHelper(node->left, tabs + 1);

}

void showTree(BST* B){
	showTreeHelper(B->root, 0);
}

/***********************************************************************/
/* Copy your previous function definitions for the functions in BST.h. */
/* PASTE THEM BELOW THIS COMMENT.                                      */
/***********************************************************************/

//your implementation for the functions in BST.h below !!!
//Create a BST Node and initialize fields
BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P)
{
	BST_NODE *new = (BST_NODE *) malloc(sizeof(BST_NODE));
	new -> left = L;
	new -> right = R;
	new -> parent = P;
	new-> key = key;
	new -> height = 0;

	return new;

}

//create BST structure and initialize fields
BST *createBST (int max)
{
	BST *bstNew = (BST *) malloc(sizeof(BST));
	bstNew -> root = NULL;
	bstNew -> maxSize = max;
	bstNew -> size = 0;

	return bstNew;
}


//check if BST is empty
int isEmpty(BST* B)
{
	if (B->root == NULL)
		return 1;

	return 0;
}


//check if BST is full
int isFull(BST* B)
{
	if (B->maxSize == B-> size)
		return 1;
	
	return 0;
}


void updateHeight(BST_NODE* current)
{
	while (current != NULL)
		{
			if ((current -> left == NULL) && (current -> right == NULL))
			{
				current -> height = 0;
			}
			//if left is NULL, return height of right
			else if ((current -> left == NULL) && (current -> right != NULL))
			{
				(current -> height) = (current -> right -> height) + 1;
			} else if ((current -> right == NULL) && (current -> left != NULL))
			{
			//if right is NULL, return height of left
				(current -> height) = (current -> left -> height) + 1;
			} else{
				//compare which is larger if both child are NOT NULL
				if ((current -> left -> height) > (current -> right -> height))
				{
					(current -> height) = (current -> left -> height) + 1;
				}else{
					(current -> height) = (current -> right-> height) + 1;
				}
			}

			current = current -> parent;
			
		}
}


// Insert a node
void insert(BST* B, BST_NODE* node)
{
	if (isFull(B) == 1)
	{
		printf("Cannot insert new node. BST is full");
		return;
	}

	if (isEmpty(B) == 1)
	{
		//insert root node
		B-> root = node;
		(B -> size) ++;
	}
	else{
		BST_NODE* current = B-> root;
		
		while (current != NULL)
		{
			//compare values
			if (node ->key > current -> key)
			{
				//go deeper when right child is not NULL
				if (current -> right != NULL)
				{
					current = current -> right;
				}else{
					// if NULL, insert new node
					current -> right = node;
					node -> parent = current;
					(B-> size) ++ ;
					break;
				}	
			}else{
				//go deeper when left child is not NULL
				if (current -> left != NULL)
				{
					current = current -> left; 
				}else{
					//insert node
					current -> left = node;
					node -> parent = current;
					(B-> size) ++ ;
					break;
				}
			}	
		}
		//update heigtht
		updateHeight(current);
	}

	
}

BST_NODE* search(BST* B, int key)
{
	//declare current variable point to root
	BST_NODE* current = B-> root;
	if (isEmpty(B) == 1)
	{
		 return current;
	}else{
		
		// search iteratively
		while (current != NULL && current -> key != key )
		{
			if (key > current -> key)
			{
				current = current -> right;
			}else{
				current = current -> left;
			}
		}

		// return addrress of current
		return current;
	}
}

//get minimum value 
BST_NODE* minimum(BST_NODE* node)
{
	if (node == NULL)
	{
		return node;
	}
	BST_NODE *minimum = node;
	while(minimum -> left != NULL)
	{
		minimum = minimum -> left;	
	}

	return minimum;
}

//get maximum value
BST_NODE* maximum(BST_NODE* node)
{
	if (node == NULL)
	{
		return node;
	}
	BST_NODE *maximum = node;
	while(maximum -> right != NULL)
	{
		maximum = maximum -> right;
	}

	return maximum;
}

//recursive delete function
int recursiveDelete (BST *B, BST_NODE* current)
{
	//case 1 : no child
	BST_NODE *c_parent = current -> parent;
	if((current -> left == NULL) && (current->right == NULL))
	{

		if(c_parent == NULL)
		{
			B-> root = NULL;
		}
		else if (c_parent-> left == current)
		{
			c_parent -> left = NULL;
		}else{
			c_parent -> right = NULL;
		}

		int key = current -> key;

		free(current);

		updateHeight(c_parent);
		return key;
	} 

	//case 2: has left child only
	if ((current -> left != NULL) && (current -> right == NULL))
	{

		BST_NODE *child = current-> left;

		if(c_parent== NULL)
		{
			B-> root = child;
			child -> parent = NULL;
		}else{
			if (c_parent-> left == current)
			{
				c_parent -> left = child;
			}else{
				c_parent -> right = child;
			}
			child -> parent = c_parent;
		}
		int key = current -> key;

		free(current);
		updateHeight(c_parent);
		return key;
	}

	//case 2: only has right child
	if ((current -> right != NULL) && (current -> left == NULL))
	{
		BST_NODE *child = current-> right;


		if(c_parent== NULL)
		{
			B-> root = child;
			child -> parent = NULL;
		}else{
			if (c_parent-> left == current)
			{
				c_parent -> left = child;
			}else{
				c_parent -> right = child;
			}

			child -> parent = c_parent;
		}
		int key = current -> key;

		free(current);
		updateHeight(c_parent);
		return key;
	}


	//case 3 - has two children

	if((current -> right != NULL) && (current -> left != NULL))
	{
		BST_NODE* predecessor = maximum(current -> left);
		current -> key = predecessor -> key;
		recursiveDelete(B, predecessor);
		int key = current -> key;
		updateHeight(c_parent);
		return key;
	}
	
	
}

//initial delete function
int delete(BST* B, int key)
{

	if (isEmpty(B) == 1)
	{
		printf("Nothing to delete! \n");
		return 0;
	}else{
		BST_NODE *current = search(B, key);

		if (current == NULL)
		{
			printf("Node not found");
			return 0;
		}else{
			//call delete function
			int key = recursiveDelete(B, current);
			B->size = B->size - 1;
			return key;
		}
		
	}
	
}

//clear all contents
void clear(BST* B)
{
	if(isEmpty(B) == 1)
	{
		printf("Nothing to delete! \n");
		return;
	}else{
		while(B->root != NULL)
		{
			//always delete the root node 
			recursiveDelete(B, B-> root);
		}
		B->size = 0;
	}
}












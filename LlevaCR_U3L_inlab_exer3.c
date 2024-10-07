//Cazhia Reese Lleva
// CMSC 123 - U3L
//Postlab exercise 3
// A C program that executes insert and search operation for a binary search tree. 
//Postlab addition: Tree traversals: inorder, preorder, and postorder



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


//function definition for the postlab exercise

//Inorder traversal recursive implementation
void printInorder (BST_NODE *current)
{
	if (current == NULL) return;
	
	printInorder(current->left);
	printf("%d ", current->key);
	printInorder(current->right);

}

//Preorder traversal recursive implementation
void printPreorder (BST_NODE *current)
{
	if (current == NULL) return;
	printf("%d ", current->key);
	printPreorder(current->left);
	
	printPreorder(current->right);

}

//Postorder traversal recursive implementation
void printPostorder (BST_NODE *current)
{
	if (current == NULL) return;
	
	printPostorder(current->left);
	
	printPostorder(current->right);
	printf("%d ", current->key);

}
int main(){

	char command;
	int key, result;

	BST *B = createBST(100);
	BST_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				insert(B, createBSTNode(key, NULL, NULL, NULL));
				break;
			case '?':
				scanf("%d", &key);
				printf("Searching node with key: %d. Location: %p\n", key, search(B, key));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(B);
				printf("\n");
				break;
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
			//for the postlab, uncomment this
			case '<':
				printf("Pre-order Traversal: ");
				preorderWalk(B);
				printf("\n");
				break;
			case '>':
				printf("Post-order Traversal: ");
				postorderWalk(B);
				printf("\n");
				break;
			
			case '/':
				printf("In-order Traversal: ");
				inorderWalk(B);
				printf("\n");
				break;
			
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}

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
		
		while (current != NULL)
		{
			
			//if left is NULL, return height of right
			if (current -> left == NULL)
			{
				(current -> height) = (current -> right -> height) + 1;
			} else if (current -> right == NULL)
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


//call recursive functions
void preorderWalk(BST* B){

	if (isEmpty(B) != 1)
	{
		printPreorder(B -> root);
	}else
		printf("Tree is empty");
	
}

void postorderWalk(BST* B){

	if (isEmpty(B) != 1)
	{
		printPostorder(B -> root);
	}else
		printf("Tree is empty");
	
}

void inorderWalk(BST* B){

	if (isEmpty(B) != 1)
	{
		printInorder(B -> root);
	}else
		printf("Tree is empty");
	
}

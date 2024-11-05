//Cazhia Reese Lleva
// CMSC 123 - U3L
// Post lab Exercise 4
// September 30, 2024

// A C program that performs binary search tree operations.
//Exercise 3: Search and delete function 
//Postlab (Exercise 3) addition: Tree traversals: inorder, preorder, and postorder
//Exercise 4: Delete function
//Postlab (Exercise 4) addition: Getting the predecessor and successor of a node (line 553)

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



void rightRotate(BST *B, BST_NODE *critical)
{
    
    BST_NODE *pivot = critical->left;

    // Perform the rotation
    critical->left = pivot->right;
    pivot->right = critical;

    // Update parent pointers
    pivot->parent = critical->parent;

    if (critical->parent == NULL) {
        // If critical was root, update the tree's root
        B->root = pivot;
    } else {
        if (critical == critical->parent->left) {
            // If critical was a left child
            critical->parent->left = pivot;
        } else {
            // If critical was a right child
            critical->parent->right = pivot;
        }
    }

    // Update critical's parent to be pivot
    critical->parent = pivot;

    // Update the left child of the critical node if it exists
    if (critical->left != NULL) {
        critical->left->parent = critical;
    }

    updateHeight(critical);
}


void leftRotate(BST*B, BST_NODE *critical)
{
	BST_NODE *pivot = critical -> right;
	critical -> right = pivot -> left;


	if (critical->right != NULL) {
        critical->right->parent = critical;
    }

	pivot->parent = critical->parent;
	
	if (critical->parent == NULL) {
        B->root = pivot;
    } else {
        if (critical == critical->parent->left) {
            critical->parent->left = pivot;
        } else {
            critical->parent->right = pivot;
        }
    }

	pivot -> left = critical;

	critical-> parent = pivot;
	updateHeight(critical);

}


int getBalance (BST_NODE *current)
{
	if (current == NULL) return 0;
    int leftHeight = (current->left != NULL) ? current->left->height : -1;
    int rightHeight = (current->right != NULL) ? current->right->height : -1;
    return leftHeight - rightHeight;
}
void checkBalance (BST *B, BST_NODE *current)
{
	
	while (current != NULL)
	{
		BST_NODE * parent = current -> parent;
		BST_NODE *pivot = NULL;
		int balanceChecker = getBalance(current);
		if(balanceChecker > 1)
		{

			pivot = current -> left;
			int pivotBalance = getBalance(pivot);
			if ((pivotBalance) < 0)
				{
					leftRotate(B, pivot);
				}

			rightRotate(B, current);
			
		}else if (balanceChecker < -1)
		{
			pivot = current -> right;
			int pivotBalance = getBalance(pivot);
			if (pivotBalance > 0)
				rightRotate(B, pivot);
			leftRotate(B, current);
		}

		current = parent;
	}
	
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
			case '-':
				scanf("%d", &key);
				printf("Removing node with key: %d\n", key);
				result = delete(B, key); // result is unused. print if u want
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
			case 'm':
				node = minimum(B->root);
				if(node) printf("Minimum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case 'M':
				node = maximum(B->root);
				if(node) printf("Maximum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(B);
				break;
			
			//uncomment this for postlab
			case '[':
				scanf("%d", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = predecessor(node);
					if(node)printf("Predecessor of %d is %d.\n", key, node->key);
					else printf("No predecessor for %d\n", key);
				}
				break;
			case ']':
				scanf("%d", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = successor(node);
					if(node)printf("Successor of %d is %d.\n", key, node->key);
					else printf("No successor for %d\n", key);
				}
				break;
			
			case 'Q':
				clear(B);
				free(B);
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
		checkBalance(B, current);

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


//Postlab exercise 4 additions

//find the predecessor
BST_NODE* predecessor(BST_NODE* node)
{
	if (node -> left != NULL)
	{
		//if left subtree is NOT NULL, get the maximum from the left subtree
		return(maximum(node -> left));
	}else{
		//else if NULL, keep going up until the lowest ancestor with a right child also an ancestor
		BST_NODE *y = node -> parent;
		while((y != NULL) && (node == y-> left))
		{
			node = y;
			y = y-> parent;
		}
		return y;
	}
}

//find the successor
BST_NODE* successor(BST_NODE* node)
{
	if (node -> right != NULL)
	{
		//if right subtree is NOT NULL find the minimum of the right subtree
		return(minimum(node -> right));
	}else{
		//else if NULL, keep going up until the lowest ancestor with a left child also an ancestor
		BST_NODE* y = node -> parent;
		while((y != NULL) &&( node == y-> right))
		{
			node = y;
			y = y-> parent;
		}
		return y;
	}
}






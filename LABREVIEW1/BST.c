#include <stdio.h>
#include <stdlib.h>
typedef struct bst_node{
    struct bst_node* left;  //left pointer
    struct bst_node* right; //right pointer
    struct bst_node* parent;//parent pointer
    int key;    //value of the node
    int height; //height of the node
} BST_NODE;

typedef struct bst{
    BST_NODE* root; //root pointer
    int maxSize;    //number of maximum nodes in the tree
    int size;   //current size of the tree
}BST;


BST * createBST(int maxSize)
{
    BST *bstNew = (BST *) malloc(sizeof(BST));
    bstNew -> root = NULL;
    bstNew -> maxSize = maxSize;
    bstNew -> size = 0;

    return bstNew;
}

BST_NODE * createBSTNode (int key, BST_NODE* L, BST_NODE* R, BST_NODE* P)
{
    BST_NODE *new = (BST_NODE *) malloc(sizeof(BST_NODE));
    new ->key = key;
    new -> left = L;
    new -> right = R;
    new -> parent = P;
    new -> height = 0;

    return new;
}

int isEmpty (BST *B)
{
    if (B -> root == NULL)
    {
        return 1;
    }

    return 0;
}

void updateHeight (BST_NODE *current)
{
    while (current != NULL)
    {
        if ((current -> right == NULL) && (current -> left == NULL))
        {
            current -> height = 0;
        }else if ((current -> right == NULL )&& (current -> left != NULL))
        {
            current -> height = (current -> left -> height) + 1;
        }else if ((current -> right != NULL) && (current -> left == NULL))
        {
            current -> height = (current -> right -> height) + 1;
        }else{
            if ((current -> right-> height) > (current -> left -> height))
            {
                current -> height =( current -> right -> height) + 1;
            }else{
                current -> height = (current -> left -> height )+ 1;
            }
        }

        current = current -> parent;
    }
}

void insert(BST *B, BST_NODE *node)
{
    if (isEmpty (B) == 1)
    {
        B -> root = node;
        (B -> size) ++;
    }else{
        BST_NODE *current = B -> root;

        while (current != NULL)
        {
            if (current -> key < node -> key)
            {
                if (current -> right == NULL)
                {
                    current -> right = node;
                    node -> parent = current;
                    (B-> size) ++;
                    break;
                }
                current = current -> right;
            }else{
                if (current -> left == NULL)
                {
                    current -> left = node;
                    node -> parent = current;
                    (B -> size) ++;
                    break;
                }
                current = current -> left;
            }
        }

        updateHeight(current);
    }
}

BST_NODE * search (BST *B, int key)
{
    BST_NODE *temp = B-> root;

    while ((temp != NULL) && (temp -> key != key))
    {
        if (key > temp -> key)
        {
            temp = temp -> right;
        }else {
            temp = temp -> left;
        }
    }

    return temp;
}

void preOrderTraversal (BST_NODE *node)
{
    if (node == NULL) return;
    printf("%d ", node -> key);
    preOrderTraversal(node -> left);
    preOrderTraversal(node -> right);
}

void preorderWalk (BST *B)
{
    if (!isEmpty(B))
    {
        preOrderTraversal(B-> root);
    }
}

void inOrderTraversal (BST_NODE *node)
{
    if (node == NULL) return;
    inOrderTraversal(node -> left);
    printf("%d ", node -> key);
    inOrderTraversal(node -> right);
}

void inorderWalk (BST *B)
{
    if (!isEmpty(B))
    {
        inOrderTraversal(B-> root);
    }
}

void postOrderTraversal (BST_NODE *node)
{
    if (node == NULL) return;
    postOrderTraversal(node -> left);
    postOrderTraversal(node -> right);
    printf("%d ", node -> key);
}
void postorderWalk (BST *B)
{
    if (!isEmpty(B))
    {
        postOrderTraversal(B-> root);
    }
}

BST_NODE * minimum (BST_NODE *node)
{
    if (node == NULL)
    return node;
    while (node-> left != NULL)
    {
        node = node -> left;
    }
    return node;
}

BST_NODE * maximum (BST_NODE *node)
{
    if (node == NULL) return node;
    while(node -> right!= NULL)
    {
       node = node -> right;
    }

    return node;
}

BST_NODE *predecessor (BST_NODE *node)
{
    if (node -> left != NULL) return maximum(node -> left);

    BST_NODE *current = node -> parent;

    while ((node != NULL) && (node == current -> left))
    {
        node = current;
        current = current -> parent;
    }

    return current;
}

BST_NODE *successor (BST_NODE *node)
{
    if (node -> right != NULL) return minimum(node -> right);

    BST_NODE *current = node -> parent;

    while ((node != NULL) && (node == current -> right))
    {
        node = current;
        current = current -> parent;
    }

    return current;
}

int deleteRecursive (BST *B, BST_NODE *node)
{
    //case 1 - no child
    BST_NODE *c_parent = node -> parent;
    if ((node -> left == NULL) && (node -> right == NULL))
    {
        if (c_parent == NULL) B->root = NULL;
        else{
            if (node == c_parent -> left)
            {
                c_parent -> left = NULL;
            }else{
                c_parent -> right = NULL;
            }
        }

        int value = node -> key;
        free(node);
        updateHeight(c_parent);
        return value;
    }

    //case 2
    if ((node -> left !=  NULL) && (node -> right == NULL))
    {
        BST_NODE *child = node -> left;
        if (c_parent == NULL) B-> root = child;
        else{
            if (node == c_parent -> left)
            {
                c_parent -> left = child;
            }else{
                c_parent -> right = child;
            }
        }
        child -> parent = c_parent;
        int value = node -> key;
        free(node);
        updateHeight(c_parent);
        return value;
    }

    if ((node -> left == NULL) && (node -> right != NULL))
    {
        BST_NODE *child = node -> right;
        if (c_parent == NULL) B-> root = child;
        else{
            if (node == c_parent -> left)
            {
                c_parent -> left = child;
            }else{
                c_parent -> right = child;
            }
        }
        child -> parent = c_parent;
        int value = node -> key;
        free(node);
        updateHeight(c_parent);
        return value;
    }


    //case 3

   if((node -> right != NULL) && (node -> left != NULL))
	{
		BST_NODE* predecessor = maximum(node-> left);
        int key = node -> key;
		node -> key = predecessor -> key;
		deleteRecursive(B, predecessor);
		return key;
	}
}

int delete (BST *B, int key)
{
    if (isEmpty(B))
    {
        return 0;
    }

    BST_NODE * node = search(B, key);
    int deleted = deleteRecursive(B, node);
    B-> size = B->size -1;
    printf("deleted: %d \n", deleted);
    return deleted;
}

// a recursive subroutine to display the BST in tree mode
void showTreeHelper(BST_NODE* node, int tabs){

	if(!node) return; // node is null, do nothing
	showTreeHelper(node->right, tabs + 1);
	for(int i=0; i<tabs; i++) printf("\t");
	printf("%d(%d)\n", node->key, node->height);
	showTreeHelper(node->left, tabs + 1);

}

void clear(BST *B)
{
    
}
void showTree(BST* B){
	showTreeHelper(B->root, 0);
}

int isFull(BST *B)
{
    return 0;
}

int getHeight (BST_NODE *node)
{

    return node -> height;
}

int recursiveSum (BST_NODE *node)
{
   if (node == NULL) return 0;

   return(recursiveSum(node-> left) + (node->height) + recursiveSum(node -> right));
}

int sumOfHeight(BST* B)
{
    if (isEmpty(B))
    {
        return 0;
    }

    int heightSum = recursiveSum (B-> root);
    return heightSum;
}

int averageHeight(BST* B)
{
    return (sumOfHeight(B)/(B->size));
}

int kthLargest (BST_NODE *node, int *k)
{
    if (node == NULL) return -1;
    int right = kthLargest(node -> right, k);
    if (*k == 0)
    {
        return right;
    }
    (*k) --;
    if(*k == 0) return node -> key;

    return (kthLargest(node -> left, k));
}


void recursiveLargest (BST_NODE *node, int * arr, int *i)
{
    if (node == NULL) return;
    recursiveLargest(node -> left, arr, i);
    arr[*i] = node -> key;
    (*i)++;
    recursiveLargest(node -> right, arr, i);
}


int kthLargestVer(BST *B, int k)
{
    int arr[B->size];
    int index = 0;
    recursiveLargest(B->root, arr, &index);

    for (int i=0; i<(B-> size); i ++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return arr[(B->size) - k];

}

int getHeightAVL(BST_NODE *node)
{
    if(node == NULL) return -1;
    return (node -> height);
}

int getBalance(BST_NODE*node)
{
    int leftHeight = getHeightAVL(node -> left);
    int rightHeight = getHeightAVL(node -> right);

    return (leftHeight - rightHeight); 
}



void leftRotate(BST *B, BST_NODE *node)
{
    BST_NODE *pivot = node -> right;
    node -> right = pivot -> left;
    if (node -> right)
        node ->right -> parent = node;
    
    pivot -> parent = node ->parent;
    if (!node -> parent)
        B-> root = pivot;
    else{
        if ((node -> parent ->right) == node)
            node -> parent -> right = pivot;
        else
            node -> parent -> left = pivot;
    }

    pivot -> left = node;
    node -> parent = pivot;
    updateHeight(node);
}

void rightRotate(BST *B, BST_NODE *node)
{
    BST_NODE *pivot = node -> left;
    node -> left = pivot -> right;
    if (node -> left)
        node ->left -> parent = node;
    
    pivot -> parent = node ->parent;
    if (!node -> parent)
        B-> root = pivot;
    else{
        if ((node -> parent ->right) == node)
            node -> parent -> right = pivot;
        else
            node -> parent -> left = pivot;
    }

    pivot -> right = node;
    node -> parent = pivot;
    updateHeight(node);
}


BST_NODE *findLCA(BST_NODE *root, int i, int j)
{
    if (root == NULL) return NULL;
    if(root-> key > i && root -> key > j) return findLCA(root->left, i, j);
    if(root-> key < i && root -> key < j) return findLCA(root->right, i, j);
    return root;
}
void AVLInsert(BST *B, BST_NODE *node)
{
    insert(B, node);
    BST_NODE *critical = node -> parent;
    BST_NODE *parent = NULL;
    BST_NODE *pivot = node;
    while(critical != NULL)
    {
        parent = critical -> parent;

        int criticalBalance = getBalance(critical);
        int pivotBalance;
        if (criticalBalance > 1)
        {
            //left heavy
            pivot = critical -> left;
            pivotBalance = getBalance(pivot);
            if (pivotBalance < 0){
                // left right leaning
                leftRotate(B, pivot);
            }
            rightRotate(B, critical);
        }else if (criticalBalance < -1)
        {
            //right heavy
            pivot = critical -> right;
            pivotBalance = getBalance(pivot);
            if (pivotBalance > 0)
            {
                //right left leaning
                rightRotate(B, pivot);
            }
            leftRotate(B, critical);
        }
        critical = parent;
    }

}

int main(){

	char command;
	int key, result, i, j;

	BST *B = createBST(100);
	BST_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				AVLInsert(B, createBSTNode(key, NULL, NULL, NULL));
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
                printf("%d ", sumOfHeight(B));
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
			case 'X':
                scanf("%d %d", &i, &j);

                BST_NODE* LCA = findLCA(B->root, i, j);
                if (!LCA){
                    printf("NULL");
                }else{
                    printf("LCA: %d \n", LCA -> key);
                }
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
            case 'k':
                scanf("%d", &key);
                int kLargest = kthLargestVer(B, key);
                printf("%d \n", kLargest);
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
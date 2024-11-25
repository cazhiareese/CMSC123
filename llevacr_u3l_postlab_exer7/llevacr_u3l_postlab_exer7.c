/*
 * Name: Cazhia Reese Lleva
 * Lab Section: CMSC 123 - U3L
 * Program Description: A C Program that demonstrates operations in the heap data structure. Mainly, it performs insert and  delete.
 * Postlab addition:
 *  The C program now performs heap sort (non-ascending) without modifying the original heap. 
*/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int left(int index){
  return(2 * index); 
}

int right(int index){
  return(2 * index + 1); 
}

int parent(int index){
  return(index / 2); 
}

void printHeapHelper(HEAP *H, int index, int tabs){
	if(index > H->size) return;
	else{
		printHeapHelper(H, right(index), tabs + 1);
		for(int i=0; i<tabs; i++) printf("\t");
		printf("%d\n", H->heap[index]);
		printHeapHelper(H, left(index), tabs + 1);
	}
}

void printHeap(HEAP *H){
	if(H!=NULL && H->size>0){
		printHeapHelper(H, 1, 0);
	}else{
		printf("Empty heap!\n");
	}
}


// IMPLEMENT FUNCTIONS HERE
HEAP* createHeap(int maxSize)
{
	//create heap structure, initialize members
	HEAP * newHeap = (HEAP *)malloc(sizeof(HEAP));
	newHeap -> size = 0;
	newHeap -> maxSize = maxSize;
	newHeap -> heap = (int *) malloc(sizeof(int) * maxSize+1);
	
	return newHeap;
}

int isFull(HEAP *H)
{
	//check if heap is full
	if (H->size == H->maxSize)
	{
		return 1;
	}

	return 0;
}

int isEmpty(HEAP *H)
{
	//check if heap is empty
	if (H->size == 0)
	{
		return 1;
	}

	return 0;
}

void clear(HEAP *H)
{
	//deletes all content from heap
	while (!isEmpty(H)) deleteM(H);
}



void insert(HEAP *H, int key)
{
	//check if full, returns error message
	if (isFull(H)){
		printf("Heap is full! Can't perform insert. \n");
		return;
	}

	//insert at size + 1
	int index = H->size  + 1;
	(H-> size) = index;
	H->heap [index] = key;
	
	
	int parent = index/2;

	int temp;

	// this performs percolate up, loop terminates only when at root or parent is already lesser than the child
	while (parent != 0 && (H->heap[parent] > H->heap[index]))
	{
		temp = H->heap[parent];
		H->heap[parent] = H->heap[index];
		H->heap[index] = temp;

		index = parent;
		parent = parent/2;
	}

}

int deleteM(HEAP *H)
{
	if (isEmpty(H))
	{
		return 0;
	}

	// swap with the last element
	int temp, leftChild, rightChild, smaller;
	int index = 1;
	int deletedKey = H->heap[index];
	temp = H->heap[index]; 
	H->heap[index] = H-> heap [H->size];
	H->heap[H->size] = temp;
	
	(H->size) --;

	// percolate down
	int heapSize = H->size;
	

	while(index < heapSize)
	{

		leftChild = index*2;
		rightChild = (index*2) +1;
		// if leftChild exists and rightChild does not
		if (leftChild <= heapSize && rightChild > heapSize)
		{
			// check if smaller than current index
			if (H->heap[leftChild] < H->heap[index])
			{
				// swap
				temp = H->heap[index];
				H->heap[index] = H->heap[leftChild];
				H->heap[leftChild] = temp;
				// if swap is performed the current index is where we swapped
				index = leftChild;
			}else{
				// if not, we preserve minHeap property
				break;
			}
		}else if (leftChild <= heapSize && rightChild <= heapSize)
		{
			// if both leftChild and rightChild exists
			// find smaller child
			if (H->heap[leftChild] < H->heap[rightChild])
				smaller = leftChild;
			else smaller = rightChild;

			// check if smaller than current index
			if (H -> heap [smaller] < H-> heap[index])
			{
				// perform swap
				temp = H->heap[index];
				H->heap[index] = H->heap[smaller];
				H->heap[smaller] = temp;
				// if swap is performed the current index is where we swapped
				index = smaller;
			} else{
				// if not, we preserve minHeap property
				break;
			}
		}else{
			// if leftChild does not exist, we break the loop (no child)
			break;
		}


	}

	return deletedKey;

}

// 
int * heapSort(HEAP *H)
{

	// Create a new heap structure
	HEAP *duplicate = createHeap(H->maxSize);
	int deleted;

	// duplicate the current heap by inserting a copy of its elements in the "duplicate" heap
	for (int i = 1; i <= H->size; i++)
	{
		insert(duplicate, H->heap[i]);
	}

	/*
	This is an implementation of the heap sort in a non-descending order
	int * sorted = (int *)malloc(sizeof(int) * H->size);
	for(int i=1; i<= H->size; i++)
	{
		deleted = deleteM(duplicate);
		sorted[i] = deleted;
	}

	return sorted;
	*/
	
	
	// Non-ascending order
	// Perform n-1 deleteMin operations

	for(int i=1; i<= (H->size)-1; i++)
	{
		deleted = deleteM(duplicate);
	}

	// restore duplicate's heap size by basing on the original's heap size
	duplicate->size = H->size;	
	// return a pointer to the heap array of the duplicate (sorted)
	return duplicate->heap;
}


int main(){

	char command;
	int key, result, type;
    int* sorted;

	HEAP *H = createHeap(30);

	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d...\n", key);
				insert(H, key);
				break;
			case '-':
				printf("Removing root from tree...\n");
				result = deleteM(H); // result is unused
				break;
			case 'p':
				printf("Printing the heap (rotated +90 degrees)...\n");
				printHeap(H);
				printf("\n");
				break;
			case 'E':
				printf("Heap %s empty.\n", isEmpty(H)?"is":"is not");
				break;
			case 'F':
				printf("Heap %s full.\n", isFull(H)?"is":"is not");
				break;
			case 'C':
				printf("Removing all contents...\n");
				clear(H);
				break;
			case '~':
				printf("The sorted version of the heap:\n");
				sorted = heapSort(H);
				for(key=1; key <= H->size; key++)
					printf("%4d", sorted[key]);
				printf("\n");
				free(sorted);
				break;
			
			case 'Q':
				free(H->heap);
				free(H);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}
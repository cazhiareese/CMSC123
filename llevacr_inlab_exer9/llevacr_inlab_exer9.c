// Cazhia Reese Lleva
// CMSC 123 - U3L
//  A C program that implements graph representation and traversal.

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"

//Implement your functions here
GRAPH *createGraph(int vertices){
	// Create graph and initialize fields
	GRAPH* newGraph = (GRAPH *) malloc(sizeof(GRAPH));
	newGraph -> num_vertices = vertices;
	newGraph -> matrix = (int **) malloc(sizeof(int *) * vertices);
	// initialize the adjacency matrix to zeros
	for (int i = 0; i < vertices ; i++)
	{
		newGraph -> matrix [i] = (int *) malloc (sizeof(int) * vertices);
		for (int j = 0; j<vertices; j++)
		{
			newGraph -> matrix [i] [j] = 0;
		}
	}

	return newGraph;
}
void insertEdge(GRAPH *G, int u, int v){
	// mark adjacent vertices in the matrix
	G->matrix[u][v] = 1;
	G->matrix[v][u] = 1;
}

int *createVisited(GRAPH *G){
	// create an array that marks visited vertices
	int * visited = (int *) malloc(sizeof(int) * G->num_vertices);

	// initialize to 0
	for (int i = 0; i < G->num_vertices; i++)
	{
		visited[i] = 0;
	}

	return visited;
}

void dfs(GRAPH *G, int start){
	
	int v;
	// create visited array
	int * visited = createVisited(G);
	// create stack and push the source vertex
	STACK * dfs_stack = createStack();
	NODE* node = createNode(start);
	push(dfs_stack, node);

	do{
		// pop top of stack
		v = pop(dfs_stack);

		// if not visited, mark as visited and print
		if(!visited[v])
		{
			visited[v] = 1;
			printf("%d ", v+1);
			// push all adjacent vertices to v that is not yet visited
			for(int i = 0; i < G->num_vertices; i++)
			{
				if(G->matrix[v][i] && !visited[i])
				{
					NODE * adj = createNode(i);
					push(dfs_stack, adj);
				}
			}
		}
	}while(!isEmpty(dfs_stack));

	free(dfs_stack);
}

void printMatrix(GRAPH *G){
	// print the adjacency matrix
	for (int i = 0; i< G->num_vertices; i++)
	{
		for(int j = 0; j<G->num_vertices; j++)
		{
			printf("%d \t", G->matrix[i][j]);
		}
		printf("\n");
	}
}

// free the adjacency matrix
void freeMatrix(GRAPH *G){
	for(int i = 0; i < G->num_vertices; i++)
	{
		free(G->matrix[i]);
	}
	free(G->matrix);	
}


// STACK OPERATIONS
// create NODE for stack (accepts data int)
NODE* createNode(int data){
	NODE *new = (NODE *) malloc(sizeof(NODE));
    new -> value = data;
    new -> next = NULL;

    return new;
}

// create stack ADT
STACK* createStack(){
	STACK *stack = (STACK *) malloc(sizeof(STACK));
    stack -> head = NULL;

    return stack;
}

// check if stack is empty
int isEmpty(STACK *L){
	if ((L -> head) == NULL){
        return 1;
    }

    return 0;
}


// push a node into the stack
void push(STACK *L, NODE* node)
{
	node -> next = L-> head;
    L-> head = node;
}

// pop a value from the stack
int pop(STACK *L){
	if ((isEmpty(L)) != 1)
    {
        NODE *temp = L -> head;
        L -> head = temp -> next;
        int returned_value = temp -> value;
        free(temp);
        return returned_value;
    }else{
        printf("List is empty");
        return 0;
    }
}


int main() {
	char command;
	int vertices, lines, u, v;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d", &u, &v);
				insertEdge(G, u-1, v-1); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				printf("\nDFS: ");
				dfs(G, 0); //0 is the initial value since we use 0-indexing (it still represents vertex 1)
				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'f':
				freeMatrix(G);
				break;
			case 'Q':
				free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}
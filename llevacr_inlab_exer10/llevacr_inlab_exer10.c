//Cazhia Reese Lleva
//2022-01742
//CMSC 123 - U3L
// A C program that performs Dijktra's Algorithm for solving the Single Shortest Path Problem


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//Implement your functions here
GRAPH *createGraph(int vertices)
{
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

void insertEdge(GRAPH *G, int u, int v, int w){
	// mark adjacent vertices in the matrix with their weight
	G->matrix[u][v] = w;
	G->matrix[v][u] = w;
}

int *createVisited(GRAPH *G){
	// create an array that marks visited vertices
	int * visited = (int *) malloc(sizeof(int) * G->num_vertices);

	// initialize to 0
	for (int i = 0; i < G->num_vertices; i++)
	{
		visited[i] = 0;
	}


	printf("\n");
	return visited;
}

int *createDistance(GRAPH *G){
	// create an array that initializes distances to 99999
	int * distance= (int *) malloc(sizeof(int) * G->num_vertices);

	// initialize to 0
	for (int i = 0; i < G->num_vertices; i++)
	{
		distance[i] = 99999;
	}

	

	return distance;
}

int *createParent(GRAPH *G){
	// create an array that marks the parent of each vertices in the path
	int * parent = (int *) malloc(sizeof(int) * G->num_vertices);

	// initialize to 0

	for (int i = 0; i < G->num_vertices; i++)
	{
		parent[i] = -1;
	}

	return parent;
}


//Dijkstra's algorithm 
void dijkstra(GRAPH *G, int source, int target){
	//initialize tracker arrays
	int * visited = createVisited(G);
	int * d = createDistance(G);
	int * p = createParent(G);

	//distance of source to itself is zero
	d[source] = 0;

	int i, minimum, j,u, v, distance,path;
	
	for (i = 0; i<G->num_vertices; i++)
	{
		//find u that is not visited and with minimum distance
		minimum = 99999;
		u = -1;
		for (j = 0; j< G-> num_vertices; j++)
		{
			if (!visited[j] && d[j] < minimum)
			{
				minimum = d[j];
				u = j;
			}
		} 
		//mark u as visited
		visited[u] = 1;


		//for every vertex v adjacent to u that is not visited, update distance
		//add u's distance to current edge weight
		for (v = 0; v<G-> num_vertices; v++)
		{
			if((G->matrix[u][v] != 0) && !visited[v])
			{
				distance = d[u] + (G->matrix[u][v]);
				if (distance < d[v])
				{
					d[v] = distance;
					p[v] = u;
				}
			}
		}
	}

	printf("\n");
	for (int i= 0; i< G->num_vertices; i++)
		printf("%d ", d[i]);
	
	printf("\n");
	for (int i= 0; i< G->num_vertices; i++)
		printf("%d ", p[i]+1);

	printf("PATH FROM %d to %d: ", source+1, target+1);
	
	//print the path
	path = target;
	while (path != -1)
	{
		printf("%d ", path+1);
		path = p[path];
	}
	printf("\n");

	printf("DISTANCE FROM %d to %d: ", source+1, target+1);
	printf("%d \n", d[target]);
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

void freeMatrix(GRAPH *G){
	for(int i = 0; i < G->num_vertices; i++)
	{
		free(G->matrix[i]);
	}
	free(G->matrix);	
}


int main() {
	char command;
	int vertices, lines, u, v, w, source, target;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d %d", &u, &v, &w);
				insertEdge(G, u-1, v-1, w); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				scanf(" %d %d", &source, &target);
				dijkstra(G, source-1, target-1);
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
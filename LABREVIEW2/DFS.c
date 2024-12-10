#include <stdio.h>
#include <stdlib.h>
typedef struct graph_tag {
	int **matrix; //holder of the adjacency matrix
	int num_vertices; //holds the vertex count
} GRAPH;


typedef struct node_tag{
	int value;
	struct node_tag* next;
}NODE;


typedef struct list_tag{
	NODE* head;
}STACK;



GRAPH * createGraph(int num_vertices)
{
    GRAPH *G = (GRAPH *) malloc(sizeof(GRAPH));
    G-> num_vertices = num_vertices;
    G -> matrix = (int **) malloc(sizeof(int *) * num_vertices);

    for (int i = 0; i<num_vertices; i++)
    {
        G->matrix[i] = (int*) malloc(sizeof(int)*num_vertices);

        for (int j = 0; j<num_vertices; j++)
        {
            G->matrix[i][j] = 0;
        }
    }

    return G; 
}

void insertEdge(GRAPH * G, int u, int v)
{
    G->matrix[u][v] = 1;
    G->matrix[v][u] = 1;
}

void printMatrix(GRAPH *G)
{

    for (int i = 0; i< G->num_vertices; i++)
	{
		for(int j = 0; j<G->num_vertices; j++)
		{
			printf("%d \t", G->matrix[i][j]);
		}
		printf("\n");
	}
}


STACK * createStack ()
{
    STACK *S = (STACK *) malloc(sizeof(STACK));

    S->head = NULL;
    return S;
}

NODE * createNODE (int value)
{
    NODE * newNode = (NODE *) malloc(sizeof(NODE));
    newNode ->value = value;
    newNode ->next = NULL;

    return newNode;
}

void push(STACK *S, NODE *node)
{
    
    node -> next = S->head;
    S->head = node;
}

int pop(STACK *S)
{
    if(S->head == NULL)
        return 0;
    
    NODE *temp = S->head;
    S->head = temp->next;
    int val = temp->value;
    free(temp);
    return val;
}

int *createVisited(GRAPH* G)
{
    int * visited = (int *) malloc(sizeof(int) * G->num_vertices);
    for (int i = 0; i<G->num_vertices; i++)
    {
        visited[i] = 0;
    }
    return visited;
}

void dfs(GRAPH *G, int source)
{
    int v;
    int *visited = createVisited(G);
    STACK *S = createStack();
    NODE *node  = createNODE(source);
    push(S, node);


    do{
        
        v = pop(S);
        if (!visited[v])
        {
            visited[v] = 1;
            printf("%2d ", v+1);
            for (int i=G->num_vertices; i>0; i--)
            {
                if(G->matrix[v][i] && !visited[i]){
                    NODE *new = createNODE(i);
                    push(S, new);
                }
            }
        }   

    }while(S->head != NULL);
}

void freeMatrix(GRAPH *G)
{
    for (int i = 0; i< G-> num_vertices; i++)
        free(G->matrix[i]);
    
    free(G->matrix);
}

void DFSRecursive (GRAPH* G, int*visited,  int source)
{
    
    visited[source] = 1;
    printf("%d ", source+1);

    for (int i = G->num_vertices; i>0; i--)
    {
        if (G->matrix[source][i] && !visited[i])
        {
            DFSRecursive(G, visited, i);
        }
    }
    
}

void DFSRec(GRAPH* G, int source)
{
    int * visited = createVisited(G);

    DFSRecursive(G, visited, source );
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
				DFSRec(G, 0); //0 is the initial value since we use 0-indexing (it still represents vertex 1)
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

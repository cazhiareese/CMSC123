//Cazhia Reese Lleva
//CMSC 123 U3L
//Postlab Exercise 1

//A C program that implements a queue ADT using linked list. It mainly features the enqueue and dequeue operations. 


#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//Extra function. Free all nodes when user exits
void freeAll (LIST *L)
{
    while (L->head != NULL)
    {     
        NODE *temp = L->head;
        L->head = L->head->next;
        printf("%d",temp->value);
        free(temp);
    
        if ((L->tail != NULL) && (L->head == L-> tail))
        {
            printf("last");
            L->tail = NULL;
        }
    }
} //end of freeAll

//main function - menu implementation
int main ()
{

     LIST *queue = (LIST *) malloc(sizeof(LIST));
    while (1)
    {
        int choice;
       
        printf("[1] Enqueue \n[2] Dequeue \n[3] Print \n[4] Exit \nChoice: ");
        scanf ("%d", &choice);
        if (choice == 1)
        {
            int value;
            printf("Enter integer: ");
            scanf("%d", &value);
            NODE * new = createNode(value);
            enqueue(queue, new);
        }else if (choice == 2)
        {
            int value_removed = dequeue(queue);
            
        }else if (choice == 3)
        {
            printQueue(queue);
        }else if (choice ==4){
            freeAll(queue);
            break;
        }else{
            printf("Invalid choice!\n");
        }
    }

}

//print queue contents from the passed queue ADT
void printQueue (LIST *L)
{
    if ((isEmpty(L)) != 1)
    {
        printf("Current List: ");
        NODE *temp = L -> head;
        while (temp != NULL)
        {
            printf("%d ", temp->value);
            temp = temp -> next;
        }

        printf("\n");
    }else{
        printf("Empty list. Nothing to print.\n");
    }
}

//create a new node when user chooses enqueue
NODE * createNode (int data)
{
    NODE *new = (NODE *) malloc(sizeof(NODE));

    //initialize node fields
    new -> value = data;
    new -> next = NULL;
    return new;
}

//create a queue ADT
LIST *createQueue()
{
    LIST *queue = (LIST *) malloc(sizeof(LIST));
    queue -> head = NULL;
    queue -> tail = NULL;

    return queue;
}


//check if queue is empty
int isEmpty (LIST *L)
{
    if ((L->head) == NULL)
    {
        return 1;
    }
    return 0;
}


//Insert at tail linked list enqueue implementation. 
void enqueue(LIST *L, NODE *node)
{   
    //Case when list is empty
    if (isEmpty(L) == 1)
    {
        L->head = node;
        L-> tail = node;
    }else{
        //make the current tail point to the new node
        L -> tail->next = node;

        //make the tail point at the newly inserted node
        L-> tail = node;
    }
}

//Delete at head linked list dequeue implementation
int dequeue (LIST *L)
{
    if ((isEmpty(L)) != 1)
    {
        //Delete at head. Return deleted value. 
        NODE *temp = L -> head;
        L -> head = temp -> next;
        int returned_value = temp -> value;
        free(temp);
        printf("Value removed: %d \n", returned_value);
        return returned_value;
    }else{
        //Queue underflow error
        printf("List is empty. Queue underflow error.\n");
        return 0;
    }
} 
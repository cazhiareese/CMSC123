#include <stdio.h>
#include <stdlib.h>

typedef struct node_tag{
    int value;
    struct node_tag* next;
}NODE;

typedef struct list_tag{
    NODE* head;
    NODE* tail;
    int length;
    int maxLength;
}LIST;


NODE* createNode (int value){
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new -> value = value;
    new -> next = NULL;

    return new;
}

LIST* createList(int limit){
    LIST *adt = (LIST *) malloc(sizeof(LIST));
    adt -> head = NULL;
    adt -> tail = NULL;
    adt -> length = 0;
    adt -> maxLength = limit;

    return adt;
}

int isFull (LIST* current){
    if (current->length == current ->maxLength){
        return 1;
    }

    return 0;
}

int isEmpty(LIST* current){
    //if length is 0?

    if (current -> head == NULL){
        return 1;
    }

    return 0;
}

void insertQueue(LIST* current, int i, NODE *new )
{
    if (isFull != 1)
    {
        int counter = 0;

        if (i == 0)
        {
            //insert at head
            new -> next = current -> head;
            current -> head = new;
        }else 
        {
            NODE *temp = current -> head;
            int counter == 0;
            while ((temp->next != NULL) && (i != counter +1))
            {
                temp = temp -> next;
                counter ++;
            }

            new -> next = temp -> next;
            temp -> next = new;
            
            if (new -> next == NULL)
            {
                current -> tail = new;
            }
        }
    } else
    {
        printf("Linked list is full! Can't insert more. ");
    }
}






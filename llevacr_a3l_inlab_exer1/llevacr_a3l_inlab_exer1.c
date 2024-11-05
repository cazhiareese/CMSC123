//Cazhia Reese Lleva
//U-3L
//A C program that implements a checker whether a parentheses in an expression are balanced and well formed.
//It utilizes a Stack ADT and its operations - mainly push and pop. 

#include <stdio.h>
#include <stdlib.h>
#include "isBalanced.h"
#include <string.h>

//main function to check if the string literal (expression) has well balanced parentheses.
int main (){

    char expression [] = "8*((6/2)+7)+3+5 (9)";


    int balance_check = isBalanced(expression);

    if (balance_check == 1){
        printf("The parentheses are balanced! \n");
    }else{
        printf("The parentheses are NOT balanced! \n");
    }
    


    return 0;
}

//check the stack content
void printStack (LIST *L)
{
    

    if ((isEmpty(L)) != 1)
    {
        NODE *temp = L -> head;
        while (temp != NULL)
        {
            printf("%d ", temp->value);
            temp = temp -> next;
        }

        printf("\n");
    }else{
        printf("*empty*\n");
    }
    
}

//create a new node whenever an opening parenthesis is encountered

NODE* createNode (int data)
{
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new -> value = data;
    new -> next = NULL;

    return new;
}

//create a stack ADT

LIST* createStack ()
{
    LIST *stack = (LIST *) malloc(sizeof(LIST));
    stack -> head = NULL;

    return stack;
}

//check if the stack is empty
int isEmpty (LIST *L)
{
    if ((L -> head) == NULL){
        return 1;
    }

    return 0;
}

//push a node at the top of the stack
void push(LIST *L, NODE* node)
{
    node -> next = L-> head;
    L-> head = node;
}

//pop a non-empty stack
int pop(LIST *L)
{
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

//isBalanced implements the algorithm
//create and push a new node when an opening parenthesis is encountered
//pop a node when a closing parenthesis is encountered
//after iterating over the expression, check if the stack is empty
int isBalanced(char *expr)
{
    LIST *stack = createStack();
    int expr_len = strlen(expr);
 

    for (int i = 0; i <= expr_len; i++)
    {

        if (expr[i] == '(')
        {
          
            NODE * new = createNode(1);
            push (stack, new);
           
        } else if (expr[i] == ')')
        {
            
            if (isEmpty(stack) == 1){
                return 0;
            }        
            int returned = pop(stack);    
        } 
        
    }

    //check list 
    if (isEmpty(stack) == 1){
        return 1;
    }

}
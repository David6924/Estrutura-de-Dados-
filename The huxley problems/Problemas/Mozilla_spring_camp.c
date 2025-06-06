#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

#define MAX 100 
struct stack {
    int current_size ; 
    int page[MAX];
};
struct stack *creat(){
    struct stack *new_stack = (struct stack*) malloc(sizeof(struct stack));
    new_stack->current_size = 0;
    return new_stack;
}
void Push (struct stack *stack, int n){
    if (stack->current_size >= MAX){
        return ; 
    }
    stack->page[stack->current_size++] = n ; 
}
int Pop (struct stack *stack){
    if (stack->current_size == 0){
        return -1 ;
    }
    return stack->page[--stack->current_size] ;
}
int Peek (struct stack *stack){
    if (stack->current_size == 0){
        return -1 ;
    }
    else {
        return stack->page[stack->current_size - 1]; 
    }
}
int main (){
    struct stack *Back = creat();
    struct stack *Forward = creat();
    int current_page = -1 ;
    char entrada[MAX]; 

    while (scanf("%s",entrada) != EOF){
        if (strcmp(entrada,"ENTER") == 0){
            Push(Back,current_page);
            current_page++;
            Forward->current_size = 0;
        }
        else if (strcmp(entrada, "BACK") == 0){
            if (Back->current_size > 0){
                Push(Forward, current_page);
                current_page = Pop(Back);
            }
        }
        else if (strcmp(entrada, "FORWARD") == 0){
            if (Forward->current_size > 0 ){
                Push(Back, current_page);
                current_page = Pop(Forward);
            }
        }
    }
    printf ("BACK: %d\n", Back->current_size -1 );
    printf ("FORWARD: %d\n", Forward->current_size );

    free(Back);
    free(Forward);
    return 0 ;
}
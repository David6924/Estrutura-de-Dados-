#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <string.h>

#define MAX 100
struct stack {
    int current_size; 
    int num[MAX];
};

struct stack *Creat (){
    struct stack *new_stack = (struct stack*)malloc(sizeof(struct stack));
    new_stack->current_size = 0;
    return new_stack; 
}
void Push(struct stack *stack , int item){
    if (stack == NULL || stack->current_size == MAX){
        return ;
    }
    stack->num[stack->current_size++] = item;
    Print(stack);
}
int Pop(struct stack *stack){
    if (stack == NULL || stack->current_size == 0){
        return -1 ;
    }
    int popped = stack->num[--stack->current_size];
    Print(stack);
    return popped;
}
void Print(struct stack *stack){
    if (stack->num == NULL || stack->current_size == 0 ){
        return ; 
    }
    for (int i = stack->current_size -1 ; i >= 0 ;i--){
        printf ("%d", stack->num[i]);
        if (i > 0){
            printf(" ");
        }
    }
    printf("\n");
   
}

int main (){
    struct stack *Pilha = Creat();
    char entrada[MAX];

    while (scanf("%s",entrada) != EOF){
        if (strcmp(entrada, "Empilhar") == 0){
            int num ; 
            scanf("%d",&num);
            Push(Pilha, num);
        }
        else if (strcmp(entrada, "Desempilhar") == 0){
            Pop(Pilha);
        }
        else if (strcmp(entrada, "Fim") == 0){
            break;
        }
    }
    return 0;
}
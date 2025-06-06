#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 100
struct stack {
    int best_element_index[MAX];
    int worse_element_index[MAX];
    int current_size ; 
    int num[MAX];
};

struct stack *Creat_stack (){
    struct stack *new_stack = (struct stack*) malloc(sizeof(struct stack));
    new_stack->current_size = 0 ;
    return new_stack;
}
int is_empty (struct stack *stack){
    return stack->current_size == 0  ;
}
void Push(struct stack *stack, int num){
    if (stack->current_size >= MAX){
        return ;
    }

    stack->num[stack->current_size] = num;

    if (stack->current_size == 0){ // O primeiro maior elemente é também o menor elemento
        stack->best_element_index[stack->current_size] = 0;
        stack->worse_element_index[stack->current_size] = 0;
    }
    else {

        stack->best_element_index[stack->current_size] = stack->best_element_index[stack->current_size - 1];
        stack->worse_element_index[stack->current_size] = stack->worse_element_index[stack->current_size - 1];

        if (num > stack->num[stack->best_element_index[stack->current_size]]){
        stack->best_element_index[stack->current_size] = stack->current_size ; 
        }
        if (num < stack->num[stack->worse_element_index[stack->current_size]]){
        stack->worse_element_index[stack->current_size] = stack->current_size;
        }
    }
    stack->current_size++;
    
}
int Pop (struct stack *stack){ // O pop tem que modificar os best_index e o worse_index
    if (is_empty(stack)){
        return -1;
    }
    int popped = stack->num[--stack->current_size ];

    return popped;
}

int Absolute (struct stack *stack){

    return abs(stack->num[stack->best_element_index[stack->current_size - 1]] - stack->num[stack->worse_element_index[stack->current_size - 1]]);

}
int main (){
    struct stack *pilha = Creat_stack();

    char entrada[MAX];
    
    while(scanf("%s",entrada) != EOF){
        

        if(strcmp(entrada,"push") == 0){
            int number; 
            scanf("%d", &number);
            Push(pilha, number);
        }
        else if (strcmp(entrada,"pop") == 0){
            int sefoi = Pop(pilha);
            printf("%d\n",sefoi);
        }
        else if (strcmp(entrada,"abs") == 0){
            int e = Absolute(pilha);
            printf("%d\n", e);
        }
        
    }
    free(pilha);
    return 0; 
}
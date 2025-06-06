#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 1000000
struct stack {
    int current_size;
    int num[MAX];
};

struct stack *creat_stack (){
    struct stack* new_stack = (struct stack*)malloc(sizeof(struct stack));
    new_stack->current_size = 0;
    return new_stack;
}
void push (struct stack *stack, int num){
    stack->num[stack->current_size++] = num;
}
int is_empty (struct stack *stack){
    return stack->current_size == 0 || stack->num == NULL ;
}
int pop (struct stack *stack){
    if (is_empty(stack)){
        return -1;
    }
    else {
        return stack->num[--stack->current_size];
    }
}
void sum (struct stack *stack){
    if (stack->current_size == 0 || stack->num == NULL){
        printf("0\n");
        return ;
    }
    int summer = 0; // Sei que summer n�o � soma em ingl�s, apenas me lembrei de uma m�sica 
    for (int i = 0 ; i < stack->current_size ; i++){
        summer += stack->num[i];
    }
    printf("%d\n", summer);
}
void pow_stack (struct stack *stack){
   if (stack->current_size == 0 || stack->num == NULL){
        printf("\n");
        return ;
   }
   for(int j = 0; j < stack->current_size; j++){
        int result = 0 ;
        result = pow(stack->num[j], 2);
        printf ("%d ",result);
        if (j >= stack->current_size){
            printf("\n");
        }
   }
}
void Avarege (struct stack *stack){
    if (stack->current_size == 0 || stack->num == NULL){
        printf("0.00\n");
        return ;
    }
    int a = 0; // Sei que summer n�o � soma em ingl�s, apenas me lembrei de uma m�sica 
    
    for (int i = 0; i < stack->current_size; i++){
        a += stack->num[i];
    }
    float ava = (float) a / stack->current_size;
    printf("%.2f\n", ava);
}
void print (struct stack *stack){
    if (stack->current_size == 0 || stack->num == NULL){
        printf("\n");
        return ;
    }
    for (int h = 0; h < stack->current_size; h++){
        printf ("%d ", stack->num[h]);
    }
    printf("\n");
    
}
int main (){
    struct stack *pilha = creat_stack();
    

    while (1){
        char entrada [MAX];
        scanf("%s", entrada);
        if (strcmp(entrada, "exit") == 0 ){
            break;
        }
        else if (strcmp(entrada, "push") == 0){
            int number; 
            scanf("%d",&number);
            push(pilha, number);
        }
        else if (strcmp(entrada, "pop") == 0){
            pop(pilha);
        }
        else if (strcmp(entrada, "pow") == 0){
            pow_stack(pilha);
        }
        else if (strcmp(entrada, "print") == 0){
            print(pilha);
        }
        else if (strcmp(entrada, "sum") == 0){
            sum(pilha);
        }
        else if (strcmp(entrada, "average") == 0){
            Avarege(pilha);
        }
    }

    free(pilha);

    return 0;
}
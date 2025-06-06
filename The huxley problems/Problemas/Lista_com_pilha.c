#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
struct node { // Cria n�s
    int *num ; 
    int current_size;
    struct node *next ; // Aponta para o pr�ximo n�
};
struct stack { // Cria um ponteiro para de n�s para o topo da pilha 
    struct node *top ; 
};

struct stack *creat_stack (){
    struct stack *stack = (struct stack*) malloc(sizeof(struct stack)); // 12 byts de mem�ria alocadas,  4 byts para o inteiro e 8 byts para o ponteiro
    stack->top = NULL ; 
    return stack;
}
void Push(struct stack *stack, int *num, int current_size){
    struct node *new_node  = (struct node*)malloc(sizeof(struct node));
    new_node->num = (int*)malloc(current_size *sizeof(int));
    memcpy(new_node->num, num, current_size *sizeof(int));
    
    new_node->current_size = current_size;
    new_node->next = stack->top; 
    stack->top = new_node;
   
}
void pop(struct stack *stack){
    if (stack->top == NULL){
        printf ("EMPTY STACK\n");
        return;
    }

     struct node *temp = stack->top ; 
    int comp = temp->current_size;   
    for(int i = 0; i < temp->current_size; i++){
        if(i+1 < comp){
            printf("%d ", temp->num[i]);
        }
        else{
            printf("%d", temp->num[i]);
        }
    }
    printf("\n");

    stack->top = temp->next;
    free(temp->num);
    free(temp);

}

int main (){
    struct stack *stack = creat_stack() ;
    char comand[10] ; 
    
    
    while(scanf(" %s",comand) != EOF){
        if (strcmp(comand,"PUSH") == 0){
            int num[1000];
            int size = 0;
            char line[1000];
            

            scanf(" %[^\n]", line);
            char *token = strtok(line, " ");

            while (token){
                num[size++] = atoi(token);
                token = strtok(NULL, " ");
            }
            Push(stack, num, size);  
        }
        else if (strcmp(comand,"POP") == 0){
            pop(stack);
        }
    }
    return 0 ;
}

/*
    Tenho que adcionar elementos nos n�s at� que que a entrada dos n�s acabem e depois cria um novo topo, ou ao contr�rio ?
*/
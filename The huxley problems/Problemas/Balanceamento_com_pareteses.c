#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 256
struct stack{
    int current_size;
    char parenteses[MAX];
};
struct stack *creat_stack(){
    struct stack *new_stack = (struct stack*)malloc(sizeof(struct stack));
    new_stack->current_size = 0;
    return new_stack;
}
void push(struct stack *stack, char p){
    stack->parenteses[stack->current_size++] = p;
}
char pop(struct stack *stack){
    if(is_empty(stack)){
        return '\0';
    }
    return stack->parenteses[--stack->current_size];
}
int is_empty(struct stack *stack){
    return stack->current_size == 0;
}
int balanced(char *parenteses){
    struct stack *entrada = creat_stack();

    for(int i = 0; parenteses[i] != '\0'; i++){
        char c = parenteses[i]; 
        if(c == '(' || c == '['){
            push(entrada,c);
        }
        else if (c == ')' || c == ']'){
            char end = pop(entrada);
            if (c == ')' && end != '(' || c ==']' && end != '[') {
                free(entrada);
                return 0;
            }
        }
    }
   
    int result = is_empty(entrada);
    free(entrada);
    return result;
}
void space_remove(char *str){
    int count = 0 ;
    for(int i = 0; str[i]; i++){
        if(!isspace(str[i])){
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main(){
    struct stack *pilha = creat_stack();
    int rep; 
    char entrada[MAX];
    scanf("%d", &rep);
    getchar();

    for (int i = 0; i < rep ; i++){
        fgets(entrada, sizeof(entrada), stdin);
        size_t len = strlen(entrada);
        if (len > 0 && entrada[len-1] == '\n'){
            entrada[len-1] = '\0';
        }
        space_remove(entrada);
        if(balanced(entrada) == 1){
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }

    return 0;
}
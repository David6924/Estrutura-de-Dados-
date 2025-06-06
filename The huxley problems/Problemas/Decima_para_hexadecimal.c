#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MAX 100
struct stack{
    int current_size; 
    char hexadecimal[MAX];
};
struct stack *Creat_new_stack (){
    struct stack *new_stack = (struct stack*)malloc(sizeof(struct stack)); 
    new_stack->current_size = 0 ;
    return new_stack;
}
void Push (struct stack *stack, char hexa){
    if (stack->current_size == MAX){
        return ; 
    }
    stack->hexadecimal[stack->current_size++] = hexa;
}
void Hexadecimal (int n){
    struct stack *transmutation = Creat_new_stack();

    if (n == 0 ){
        Push(transmutation, '0');
    }
    while (n != 0){
        int mod = n % 16 ;
        if (mod == 10){
            Push(transmutation, 'A');
        }
        else if (mod == 11){
            Push(transmutation, 'B');
        }
        else if (mod == 12){
            Push(transmutation, 'C');
        }
        else if (mod == 13){
            Push(transmutation, 'D');
        }
        else if (mod == 14){
            Push(transmutation, 'E');
        }
        else if (mod == 15){
            Push(transmutation, 'F'); 
        }
        else {
            Push(transmutation, '0' + mod);
        }
        n = n /16 ; 
    }
    for (int i = transmutation->current_size -1 ; i >= 0; i--){
        printf("%c", transmutation->hexadecimal[i]);
    }
    
    free(transmutation);
}
int main (){
    int n; 
    scanf ("%d",&n); // O que vai entrar na fun��o heaxadecimal 
    Hexadecimal(n);
    return 0 ; 
}
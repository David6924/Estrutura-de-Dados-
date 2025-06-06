#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack(){
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->head = NULL;
    return stack;
}
NODE* create_node(int element){
    NODE* node = (NODE*) malloc(sizeof(NODE));
    node->element = element;
    node->next = NULL;
    return node;
}

int IS_EMPTY(STACK* stack){
    return stack->head == NULL;
}
int POP(STACK* stack){
    if (IS_EMPTY(stack)){
        abort();
    }
    NODE* top = stack->head;
    int element = top->element;
    stack->head = top->next;
    free(top);
    return element;
}
void PUSH(STACK* stack, int element){
    NODE* node = create_node(element);
    node->next = stack->head;
    stack->head = node;
}
void result(STACK* stack, char operation){
    int b = POP(stack);
    int a = POP(stack);
    int res;
    if (operation == '+'){
        res = a + b;
    }
    else if (operation == '-'){
        res = a - b; 
    }
    else if (operation == '*'){
        res = a * b ;
    }
    else if (operation == '/'){
        res = a / b ;
    }
    else {
        abort();
    }
    PUSH(stack, res);

    
}
void Calculadora(STACK* calculadora, int size){
    char token[10];

    for (int i = 0; i < size; i++){
        scanf("%s", token);

        if (token[0] >= '0' && token[0] <='9'){
            PUSH(calculadora,atoi(token));
        }
        else {
            result(calculadora,token[0]);
        }
    }
}

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));

}
//Insira o código aqui
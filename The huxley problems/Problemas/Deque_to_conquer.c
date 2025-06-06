#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _deque deque_t;
typedef struct _node   node_t;

//Guarda um ponteiro pro node anterior, para o proximo node e o valor guardado
struct _node {
	node_t *prev;
  	node_t *next;
  	int    value;
};

//Guarda um ponteiro para o primeiro node, um ponteiro para o ultimo node, e o tamanho do deque
struct _deque {
  	node_t *front;
  	node_t  *rear;
  	int      size;
};

//Cria um node que guarda os valores que são enfileirados no deque
node_t *node_new(int value){
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL){
        abort();
    }
    node->value = value ;
    node->prev = NULL;
    node->next = NULL;
    return node;

}
deque_t* construct    (){
    deque_t* deque = (deque_t*)malloc(sizeof(deque_t));
    if (deque == NULL){
        abort();
    }
    deque->front = NULL ;
    deque->rear = NULL;
    deque->size = 0;
    return deque;
}

void     destruct     (deque_t *deque){
    node_t *current = deque->front;
    while(current != NULL){
        node_t *temp = current;
        current = current->next;
        free(temp);
    }
    free(deque);
}

int      size         (deque_t *deque){
    return deque->size;
}

bool     empty        (deque_t *deque){
    return deque->size == 0;
}
int      front        (deque_t *deque){
    if (empty(deque)){
        return -1;
    }
    return deque->front->value;
}

int      rear         (deque_t *deque){
    if(empty(deque)){
        return -1;
    }
    return deque->rear->value;
}
void     enqueue_rear (deque_t *deque, int value){
    node_t* node = node_new (value);
    if (empty(deque)){
        deque->front = node ;
        deque->rear = node ;
    }
    else {
        node->prev = deque->rear;
        deque->rear->next = node;
        deque->rear = node;
    }
    deque->size++;
}

void     enqueue_front(deque_t *deque, int value){
    node_t* node = node_new (value);
    if (empty(deque)){
        deque->front = node ;
        deque->rear = node ;
    }
    else {
        node->next = deque->front;
        deque->front->prev = node;
        deque->front = node;
    }
    deque->size++;
}

void     dequeue_rear (deque_t *deque){
    if(empty(deque)){
        return;
    }
    node_t* temp = deque->rear;
    if(deque->front == deque->rear){
        deque->front = NULL;
        deque->rear = NULL ;
    }
    else {
        deque->rear = temp->prev;
        deque->rear->next = NULL ;
    }
    free(temp);
    deque->size--;
}
void     dequeue_front(deque_t *deque){
    if (empty(deque)){
        return;
    }
    node_t* temp = deque->front;
    if (deque->front == deque->rear){
        deque->front = NULL;
        deque->rear = NULL;
    }
    else {
        deque->front = temp->next;
        deque->front->prev = NULL;
    }
    free(temp);
    deque->size--;
}

void     erase        (deque_t *deque){
    while(!empty(deque)){
        dequeue_front(deque);
    }
}
void     print        (deque_t *deque){
    node_t* current = deque->front;
    while(current != NULL){
        printf("%d", current->value);
        if (current->next != NULL){
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
 	int i, num;
  	scanf("%d", &num);
  
  	deque_t* deque = construct();
  
  	int vector[num];
  	for(i = 0; i < num; ++i)
      	scanf("%d", &vector[i]);
  
  	for(i = 0; i < num; ++i)
      	enqueue_rear(deque, vector[i]);
  
 	printf("%d\n", front(deque));
  	printf("%d\n", rear (deque));
  
  	if(!empty(deque))
  		printf("The size of the deque %d\n", size(deque));
  	else
       	printf("The deque is empty\n");
  	
    scanf("%d", &num);
    for(i = 0; i < num; ++i)
       enqueue_front(deque, i);
  	print(deque);
    dequeue_front(deque);
    print(deque);
    dequeue_rear (deque);
    print(deque);
    
  	erase(deque);
  	for(i = 0; i < 3; ++i)
  		enqueue_rear(deque, i);
  		
  	print(deque);
    destruct(deque);
       
	return 0;
}






//Insira o código aqui
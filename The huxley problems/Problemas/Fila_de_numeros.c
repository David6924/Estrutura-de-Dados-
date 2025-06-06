#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#define MAX 100 
struct queue {
    int current_size ;
    int head ; 
    int tail; 
    int items [MAX]; 
};
struct queue *Creat_queue (){
    struct queue *new_queue = (struct queue*)malloc(sizeof(struct queue));
    new_queue->head = 0; 
    new_queue->tail = MAX -1;
    new_queue->current_size = 0 ;
    return new_queue;
}
void enqueue (struct queue *queue, int item){ // PUSH
    if (queue->current_size == MAX){
        return;
    }
    queue->tail = (queue->tail+1) % MAX ;
    queue->items[queue->tail] = item ;
    queue->current_size ++ ;
}
int dequeue(struct queue *queue){ // POP
    int dequeued = queue->items[queue->head];
    queue->head = (queue->head + 1) % MAX;
    queue->current_size -- ;
    return dequeued;
}
int sum (struct queue *queue){ // SUM
    if (queue->current_size == 0){
        abort();
    }
    int summer = 0 ;
    for (int i = 0; i < queue->current_size; i++){
        int index = (queue->head + i) % MAX ;
        summer += queue->items[index];
    }
    return summer ;
}
void print (struct queue *queue){
    if (queue->current_size == 0){
        return ; 
    }
    for (int i = 0 ; i < queue->current_size ; i++){
        int index = (queue->head + i) % MAX ;
        printf("%d ", queue->items[index]);
    }
    printf("\n");
}
int main (){
    struct queue *Fila = Creat_queue();

    while (1){
        char entrada [MAX];
        scanf("%s", entrada);
        if (strcmp(entrada, "exit") == 0 ){
            break;
        }
        else if (strcmp(entrada, "push") == 0){
            int number; 
            scanf("%d",&number);
            enqueue(Fila, number);
        }
        else if (strcmp(entrada, "pop") == 0){
            dequeue(Fila);
        }
        else if (strcmp(entrada, "sum") == 0){
            int soma = sum(Fila);
            printf("%d\n",soma);
        }
        else if (strcmp(entrada, "print") == 0){
            print(Fila);
        }
    }
    return 0; 
}
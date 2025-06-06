#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 101

struct node {
    int item; 
    struct  node *next ; 
};

struct node * creat_linked_list (){
    return NULL ; 
}
int is_empty (struct node *head){
    return head == NULL; 
}

struct node *add (struct node *head, int item){
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->item = item ; 
    new_node->next = NULL ; 
    
    if (head == NULL){
        return new_node ;
    }

    struct node *temp = head; 

    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new_node;
    return head ;
}
void counting(struct node *head){
    int current_end = 0, best_start = -1, best_end = -1 ; 
    int current_start = -1 , position = 0;
    
    
    while (head != NULL){
        if (head->item == 0){
            if (current_start == -1){
                current_start = position ;
            }
            current_end = position ;   
        }
        else {
            if (current_start != -1 && (current_end - current_start) > (best_end - best_start)){
                best_start = current_start;
                best_end = current_end ; 
            }
            current_start = -1 ; 
        }
        if (head->next != NULL){
            position ++ ;
        }
        head = head->next ;
        
    }
    if (current_start != -1 && (current_end - current_start) > (best_end - best_start)){
        best_start = current_start; 
        best_end = current_end ; 
    }
    if (best_end != -1){
        printf ("%d %d\n", best_start , best_end);
    }
    else {
        printf ("%d %d\n", position, position);
    }
   
}
void liberar(struct node *list){
    struct node *aux;
    while (list){
        aux = list;
        list = list->next;
        free(aux);
    }
}
int main (){
    char num[MAX]; 

    while (scanf ("%s", num) && strcmp(num, "0") != 0){
        struct node *list = creat_linked_list() ; 
        for (int i = 0 ; i < strlen(num); i++){
            list = add(list, num[i]-'0');
        }
        counting(list);
        liberar(list);
    }

    

    return 0 ;
}
/*
    01100010
    1� Execu��o 101100010 % 10 = 0  current = 0 previous = 0 zero_counter = 1 previous_counter = 0 zero_previous counter = 0
    2� Execu��o 10110001 % 10 != 0  current = 1 previous = 0 zero_counter = 0 previous_counter = 1 zero_previous counter = 1
    3� Execu��o 1011000 % 10 = 0    current = 2 previous = 2 zero_counter = 1 previous_counter = 1
    4� Execu��0 101100 % 10 = 0     current = 3 previous = 2 zero_counter = 2 previous_counter = 1
    5� Execu��o 10110 % 10 = 0      current = 4 previous = 2 zero_counter = 3 previous_counter = 1
    6� Execu��o 1011 % 10 != 0      current = 5 previous = 2 zero_counter = 0 previous_counter = 2 zero_previous counter = 3 <-- Parei aqui
    .
    . 
    . 

    vou ter que inverter a lista encadeada 
*/
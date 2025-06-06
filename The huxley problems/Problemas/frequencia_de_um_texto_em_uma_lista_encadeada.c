#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

struct node {
    char txt ;
    int freq ; 
    struct node *next ; 
};
struct node *creat_a_linked_list(){
    return NULL ; 
}

void frequence (struct node **head, char texto ){
    struct node *new_node = (struct node*) malloc(sizeof(struct node)); 
    new_node->txt = texto ; 
    new_node->freq = 1 ; 
    new_node->next = NULL ;
    
    if(*head == NULL || texto > (*head)->txt ){
        new_node->next = *head;
        *head = new_node;
        return;
    }

    struct node *temp = *head;
    if (temp->txt == texto){
        temp->freq += 1;
        free(new_node);
    }
    else {
        while(temp->next != NULL && texto < temp->next->txt){
            temp = temp->next;
        }
        if(temp->next != NULL && temp->next->txt == texto){
            temp->next->freq += 1;
            free(new_node);
        }
        else{
            new_node->next = temp->next;
            temp->next = new_node ;
        }
    }
}

void free_memory(struct node *list){
    struct node *aux;
    while (list){
        aux = list;
        list = list->next;
        free(aux);
    }
}
void print_linked_list(struct node* head){
    while (head != NULL){
        printf ("%c %d\n", head->txt , head->freq);
        head = head->next ; 
    }
}

int main (){
    struct node *list = creat_a_linked_list() ; 
    char Texto;
    
    while ((Texto=getchar())!=EOF){
        frequence(&list, Texto);
    }
    print_linked_list(list) ;
    free_memory(list);
    

    return 0 ; 
}

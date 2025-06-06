#include <stdio.h>
#include <stdlib.h>
struct node { // Errei aqui quando eu não tinha colocado o nome da struct 
    int item ; 
    struct node *next; 
};

struct node *creat_linked_list (){ // Tenho que citar a struct toda a vez que eu chamar node 
    return NULL ;
}
int is_empty (struct node *head){
    return head == NULL ; 
}
struct node *add (struct node *head, int item){
    struct node *new_node = (struct node*) malloc(sizeof(struct node)); 
    new_node->item = item ; 
    new_node->next = head ;
    return new_node ; 

}
struct node* search (struct node *head, int item){
    while (head->item != NULL){
        if (head->item == item){
        return head ; 
    }
        head = head->next;
    } 
    return NULL ; 
}
struct node* remove_node(struct node* head, int item){ // Não consegui entender completamente essa função 
    struct node* previous = NULL ; 
    struct node* current = head ; 
    while (current != NULL && previous != item){
        previous = current ; 
        current = current->next ;
    }
    if (current == NULL) { 
        return head ; 
    } 
    else {
        previous->next = current->next ; 
    }
    free(current);
    return head ; 
}
void print_linked_list(struct node* head){
    while (head != NULL){
        printf ("%d\n", head->item);
        head = head->next ; 
    }
}
int main (){
    struct node* list = creat_linked_list();
    int item ; 
    while (scanf ("%d",&item) != EOF){
        list = add(list, item );
    }
    print_linked_list (list); 
    return 0 ; 
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node { 
    int number ; 
    struct node *next ; 
}; 

struct node *creat_a_linked_list (){
    return NULL ; 
}
struct node *is_empty (struct node *head){
    return head == NULL ;
}
struct node *add_operations(struct node *head, int number){
    struct node *op = (struct node*) malloc(sizeof(struct node));
    op->number = number ; 
    op->next = head ; 
    return op ; 
}

struct node *operation_list(struct node *head_one, struct node *head_two){
    struct node *result = creat_a_linked_list() ; 
    int carry = 0 ; 
    while (head_one != NULL || head_two != NULL || carry ){ // PAra o caso de um dos dois não ter menhum contudo, como se fosse uma elemento neutro
        int s = carry ; 
        if(head_one != NULL){
            s += head_one->number ; 
            head_one = head_one->next;
        }
        if (head_two != NULL){
            s += head_two->number ; 
            head_two = head_two->next; 
     
        }

        carry = s / 10; 
        int digit = s%10 ;
        result = add_operations (result, digit);
    }
    while (result != NULL && result->number == 0 && result->next != NULL){
        struct node *temp = result ; 
        result = result->next ; 
        free(temp);
    }
    return result ;
}
void print_linked_list(struct node* head){
    if(is_empty(head)){
        printf("Lista vazia!\n");
    }
    while (head != NULL){
        printf ("%d ", head->number);
        head = head->next ; 
    }
    printf("\n");
}
void free_memory(struct node *list){
    struct node *aux;
    while (list){
        aux = list;
        list = list->next;
        free(aux);
    }
}

int main (){
    struct node *sum_one = creat_a_linked_list(); 
    struct node *sum_two = creat_a_linked_list();
    char numbers[2] ;

    while (scanf("%1s",numbers) && strcmp(numbers, "+") != 0 ){
        sum_one = add_operations(sum_one, atoi(numbers));
    }
    while (scanf("%1s",numbers) && strcmp(numbers, "=") != 0 ){
        sum_two = add_operations(sum_two, atoi(numbers));
    }
    
    
    struct node *result = operation_list(sum_one, sum_two); 

    print_linked_list(result); 

    free_memory (sum_one);
    free_memory (sum_two);
    free_memory (result);
    return 0 ;
}
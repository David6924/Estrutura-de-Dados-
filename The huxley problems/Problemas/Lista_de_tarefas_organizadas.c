#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
struct list {
    char *task ; 
    int priority ;
    struct list *next ;
};
struct list *creat_linked_list(){
    return NULL ;
}
struct list *is_empty (struct list *head){
    return head == NULL ;
}
struct list *add_to_the_tesk (struct list *head, char *task, int priority){
    struct list *new_task = (struct list*) malloc(sizeof(struct list));
    new_task->task = strdup(task) ; 
    new_task->priority = priority ; 
    new_task->next = head ; 

    return new_task ;
}
struct list *in_order (struct list *head){
    struct list *sorted = creat_linked_list();
    struct list *current = head ;

    while (current != NULL ){
        struct list *next = current->next;

        if (sorted == NULL || sorted->priority > current->priority){
            current->next = sorted;
            sorted = current; 
        }
        else {
            struct list *temp = sorted;

            while (temp->next != NULL && temp->next->priority <= current->priority){
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current ;
        }
        current = next ; 
    }
    return sorted ; 

    
}
void print_linked_list(struct list* head){
    if(is_empty(head)){
        printf("\n");
        return;
    }
    while(head != NULL){
        printf("%d. %s\n", head->priority, head->task );
        head = head->next ; 
    }
    
}
void free_memory(struct list *list){
    struct list *aux;
    while (list){
        aux = list;
        free(aux->task);
        list = list->next;
        free(aux);
    }
}
int main (){
    int call ; 
    /*
        0 -> Feicha o programa
        1 -> Adcionar Nova task
        2 -> Exibir as tasks
    */
   struct list *Duty = creat_linked_list();
    while (1){
        

        scanf("%d",&call) ;

        if  (call == 0){
            break;
        }
        if (call == 1){
            char task[100];
            int prio;

            scanf(" %[^\n]", task);
            scanf("%d", &prio);
            Duty = add_to_the_tesk(Duty, task , prio);
        }
        if (call == 2){
            Duty = in_order(Duty);
            printf("\n");
            print_linked_list(Duty);
        }
    }
    free_memory(Duty);
    return 0 ; 
}
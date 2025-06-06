#include <stdio.h>
#include <stdlib.h>
/*
    David não se esqueça que esse código que você pegou de ordenação é plagiado, não envie ele no The huxley. 
    Entenda ele primeiro e depois o modifique. 
*/
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
struct node *find_middle(struct node *head){
    if (head == NULL) return NULL ; // Se não tiver nada dentro da lista vai retornar NULL

    struct node *slow = head;  
    struct node *fast = head->next; 

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next; // Avança um nó por interação
        fast = fast->next->next; // Avança dois nós por interção 
    }
    return slow; // Quando fast chegar ao final, slow estará no meio da lista encadeada
}
struct node *merge(struct node *left, struct node *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    struct node *result = NULL;

    // Escolhe o menor valor entre os dois nós iniciais
    if (left->item <= right->item) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

// Função principal do Merge Sort
struct node *merge_sort(struct node *head) {
    // Caso base: se a lista estiver vazia ou tiver apenas um nó
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Encontra o meio da lista
    struct node *middle = find_middle(head);
    struct node *next_to_middle = middle->next;

    // Divide a lista em duas metades
    middle->next = NULL;

    // Ordena recursivamente as duas metades
    struct node *left = merge_sort(head);
    struct node *right = merge_sort(next_to_middle);

    // Combina as duas metades ordenadas
    return merge(left, right);
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
    list = merge_sort(list);
    print_linked_list (list); 
    return 0 ; 
}
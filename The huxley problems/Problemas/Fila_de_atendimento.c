#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
struct Person {
    int ID; 
    int Age; // Age vai ser o nosso priority
};
struct node {
    struct Person pessoa; 
    struct node *next;
};
struct queue {
    struct node *head ;
    struct node *tail ;
};

void Creat (struct queue *f){
    f->head = NULL;
    f->tail = NULL ;
}
struct Person createPerson (int id, int age) {
    struct Person p ;
    p.ID = id ;
    p.Age = age;
    return p;
}
void enqueue (struct queue *f, int ID , int AGE){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->pessoa.ID = ID ; 
    new->pessoa.Age = AGE;
    new->next = NULL; 

    if (f->tail == NULL){
        f->head = new;
        f->tail = new;
    }
    else {
        f->tail->next = new;
        f->tail = new;
    }
}
struct Person dequeue(struct queue *f){
    struct Person p = createPerson(-1, -1); // Caso no qual tem anada ainda
    if (f->head == NULL){
        return p;
    }
    struct node *temp = f->head;
    p = temp->pessoa;
    f->head = f->head->next;
    
    if (f->head == NULL){
        f->tail = NULL;
    }
    free(temp);
    return p;
}
void print (struct queue *f){
    struct node *current = f->head;
    while (current != NULL){
        printf("ID: %d IDADE: %d\n", current->pessoa.ID , current->pessoa.Age);
        current = current->next;
    }
}
int is_empty(struct queue *f){
    return f->head == NULL;
}

int main() {
    struct queue Old ; 
    Creat(&Old);
    struct queue Young ;
    Creat(&Young);

    int n; 
    scanf("%d", &n);
    getchar();

    char entrada[50];
    int id, age; 
    int i_atendidos = 0; 

    while (1){
        scanf("%s", entrada);
        
        if (strcmp(entrada,"f") == 0){
            break;
        }
        else if (strcmp(entrada,"a") == 0){
            scanf("%d %d", &id, &age);
            if (age > 60){
                enqueue(&Old, id, age);
                
            }
            else {
                enqueue(&Young, id, age);
                
            }
        }
        else if (strcmp(entrada,"r") == 0){
            if (!is_empty(&Old) && (i_atendidos < n || is_empty(&Young))){
                struct Person p = dequeue(&Old);
                i_atendidos++;
                printf("\n");
            }
            else if (!is_empty(&Young)){
                struct Person p = dequeue(&Young);
                i_atendidos = 0;
                printf("\n");
            }
        }
        else if (strcmp(entrada,"i") == 0){
            printf ("\nfila de idosos:\n");
            if (!is_empty(&Old)){
                print(&Old);
            }
            else {
                printf("fila vazia!\n");
            }
            printf("fila de nao-idosos:\n");
            if (!is_empty(&Young)){
                print(&Young);
            }
            else {
                printf("fila vazia!\n");
            }
            printf("----------\n");
        }
    }
	return 0;
}
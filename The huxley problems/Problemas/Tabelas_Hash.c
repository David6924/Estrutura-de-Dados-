#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node{
    int item;
    struct node*next;
};
struct hash_node{
    int tam ;
    struct node **table;
    int count;
};
struct node *creat_node(int item){
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->next = NULL;
    return new_node;
}
int division_method (int key, int tam){
    return key % tam ;
}
struct hash_node *creat_hash_table(int tam){
    struct hash_node *new_hash_table = (struct hash_node*)malloc(sizeof(struct hash_node));

    new_hash_table->tam = tam;
    new_hash_table->count = 0;
    new_hash_table->table = (struct node**)malloc(tam * sizeof(struct node*));

    for (int i = 0 ; i < tam ; i ++){
        new_hash_table->table[i] = NULL;
    }

    return new_hash_table;
}
void Put (struct hash_node *ht, int item){
    int h = division_method(item, ht->tam);
    struct node *new_node = creat_node(item);

    if (ht->table[h] == NULL || item < ht->table[h]->item){
        new_node->next = ht->table[h];
        ht->table[h] = new_node;   
    }
    else {
        struct node *current = ht->table[h];
        while(current->next != NULL && current->next->item < item){ // Organiza os valores
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }

    ht->count++;
}
void remove_item (struct hash_node *ht, int item){
    int h = division_method(item, ht->tam);

    if(ht->table[h] == NULL){
        return;
    }
    if(ht->table[h]->item == item){
        struct node *temp = ht->table[h];
        ht->table[h] = ht->table[h]->next;
        free(temp);
        ht->count--;
        return;
    }
    struct node *current = ht->table[h];
    while (current->next != NULL && current->next->item != item){
        current =current->next;
    }
    if (current->next != NULL){
        struct node *temp = current->next;
        current->next = current->next->next;
        free(temp);
        ht->count--;
    }
}
void print (struct hash_node *ht){
    printf("imprimindo tabela hash:\n");

    for (int i = 0; i< ht->tam; i++){
        printf("[%d]:", i);

        if(ht->table[i] == NULL){
            printf("Lista vazia!\n");
        }
        else{
            struct node *current = ht->table[i];
            while(current != NULL){
                printf("%d=>", current->item);
                current = current->next;
            }
            printf("\n");
        }
    }
}
void search(struct hash_node *ht, int value){
    int h = division_method(value, ht->tam);
    int access = 0; 
    int found = 0;

    printf("BUSCA POR %d\n", value);
    printf("numero de elementos da tabela hash: %d\n", ht->count);

    if (ht->table[h] != NULL){
        struct node *current = ht->table[h];
        while (current != NULL){
            access++;
            if (current->item == value){
                found = 1;
                break;
            }
            current = current->next;
        }
    }
    if (found){
        printf("elemento %d encontrado!\n", value);
    }
    else {
        printf("elemento nao encontrado!\n");
    }
    printf("numero de elementos acessadis na tabela hash: %d\n",access);
}   
int main (){
    int tam; 
    scanf("%d",&tam);

    struct hash_node *ht = creat_hash_table(tam);

    char entrada;
    int num ;

    while (1){
        scanf(" %c", &entrada);

        if (entrada == 'a'){ //add
            scanf("%d", &num);
            Put(ht,num);
        }
        else if (entrada == 'r'){ // remove
            scanf("%d", &num);
            remove_item(ht,num);
        }
        else if (entrada == 'i'){ // imprimir
            print(ht);
        }
        else if (entrada == 'p'){ // get
            scanf("%d", &num);
            search(ht,num);
        }
        else if (entrada == 'f'){ // Finaliza
            break;
        }
       
    }
    return 0;
}
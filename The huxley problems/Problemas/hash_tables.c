#include <stdio.h> 
#include <string.h> 
#include <math.h> 
#include <stdlib.h>

struct node {
    int item;
    struct node *next;
};
struct hash_node{
    int tam ;
    struct node **table;
    int count;
};
struct node *creat_node (int item){
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->next = NULL;
    return new_node;
}
int hash (int key, int tam){
    return key % tam ;
}
struct hash_node *creat_hash(int tam){
    struct hash_node *new_hash = (struct hash_node*) malloc(sizeof(struct hash_node));
    new_hash->tam = tam;
    new_hash->count = 0 ;
    new_hash->table = (struct node**)malloc(tam * sizeof(struct node*));

    for (int i = 0; i< tam; i++){
        new_hash->table[i] = NULL;
    }
    return new_hash;
}
void PUT (struct hash_node *ht, int item){
    int h = hash(item, ht->tam);
    struct node *new_node = creat_node(item);

    if (ht->table[h] == NULL ){
        ht->table[h] = new_node;
    }
    else {
        struct node *current = ht->table[h];
        while(current->next != NULL){
            current = current->next;
        }
        
        current->next = new_node;
    }
    ht->count++;
}
void print (struct hash_node *ht){

    for (int i = 0; i< ht->tam; i++){
        printf("%d -> ", i);

        if(ht->table[i] == NULL){
            printf("\\\n");
        }
        else{
            struct node *current = ht->table[i];
            while(current != NULL){
                printf("%d -> ", current->item);
                current = current->next;
            }
            printf("\\\n");
        }
    }
}
void free_hash(struct hash_node *ht){
    for (int i = 0 ; i < ht->tam; i++){
        struct node *current = ht->table[i];
        while (current != NULL){
            struct node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}
int main (){

    int c ; // Numero de casos 
    scanf("%d",&c); 
    

    for(int i = 0; i < c; i++){
        int size, tam ; 
        scanf("%d %d",&size, &tam);
        struct hash_node *ht = creat_hash(size);
        for (int j = 0; j < tam ; j++){
            int item;
            scanf("%d",&item);
            PUT (ht,item);
        }
        print(ht);
        if (i < c -1){
            printf("\n");
        }
        free_hash(ht);
    }
    return 0;
}
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node {
    int item;
    struct node* next;
};
struct hash_node{
    int tam ; 
    int count;
    struct node **table;
};
struct node *creat_node (int item ){
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->next = NULL;
    return new_node;
}
int hash(int key, int tam){
    return key % tam;
}
struct hash_node *creat_hash (int tam){
    struct hash_node *ht = (struct hash_node*) malloc(sizeof(struct hash_node));
    ht->tam = tam ;
    ht->count = 0 ;
    ht->table = (struct node**)calloc(tam , sizeof(struct node*)); // A questão pediu que ia aumentar
    return ht;
}

int maior (struct hash_node *ht){
    int maxtam = 0 ;

    for (int i = 0; i < ht->tam; i++){
        int atutam = 0 ;
        struct node *current = ht->table[i];

        while (current != NULL){
            atutam++;
            current = current->next;
        }
        if (atutam > maxtam){
            maxtam = atutam ; 
        }
    }
    return maxtam;
}

void rehash (struct hash_node* ht){
    int newsize = 2 * ht->tam - 1 ;
    struct node** new_table = (struct node **)calloc(newsize, sizeof(struct node*));

    for (int i = 0; i < ht->tam ; i++){
        struct node* current = ht->table[i];

        while (current != NULL){
            struct node *next = current->next;
            int newh = hash(current->item, newsize);
            current->next = new_table[newh];
            new_table[newh] = current;
            current = next;
        }
    }
    free(ht->table);
    ht->table = new_table;
    ht->tam = newsize;
}
bool add(struct hash_node *ht, int item, int *cmp){
    int h = hash(item, ht->tam);
    *cmp = 0 ;

    struct node *current = ht->table[h];
    while (current != NULL){
        (*cmp)++;
        if (current->item == item){
            return false;
        }
        current = current->next;
    }
    struct node *new_node = creat_node(item);
    new_node->next = ht->table[h];
    ht->table[h] = new_node;
    ht->count++;

    double load = (double)ht->count/ht->tam;
    if (load >= 0.75){
        rehash(ht);
    }
    return true;
}
bool del (struct hash_node *ht, int item, int*cmp){
    int h = hash(item, ht->tam);
    *cmp = 0 ;
    struct node *current = ht->table[h];
    struct node *previous = NULL ;

    while (current != NULL){
        (*cmp)++;

        if(current->item == item){
            if (previous == NULL){
                ht->table[h] = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current);
            ht->count--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}
bool has(struct hash_node *ht, int item, int*cmp){
    int h = hash(item, ht->tam);
    *cmp = 0 ;

    struct node *current = ht->table[h];

    while (current != NULL){
        (*cmp)++;
        if (current->item == item){
            return true;
        }
        current = current->next;
    }
    return false;
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
    struct hash_node *ht = creat_hash(7);
    char entrada[10];
    int num, count = 0;
    int cmp ;

    while (scanf("%s", entrada) != EOF){
        if (strcmp(entrada, "ADD") == 0){
            scanf("%d", &num);
            bool result = add(ht, num, &cmp);
            printf("%d %d %d\n", count, result ? 1 : 0, cmp);
        }
        else if (strcmp(entrada, "DEL") == 0){
            scanf("%d", &num);
            bool result = del(ht, num, &cmp);
            printf("%d %d %d\n", count, result ? 1 : 0, cmp);
        }
        else if (strcmp(entrada, "HAS") == 0){
            scanf("%d", &num);
            bool result = has(ht, num, &cmp);
            printf("%d %d %d\n", count, result ? 1 : 0, cmp);
        }
        else if (strcmp(entrada, "PRT") == 0){
            int maiorlista = maior(ht);
            printf("%d %d %d %d\n", count, ht->tam, ht->count, maiorlista);
        }
        count++;
    }

    free_hash(ht);
    return 0 ;
}
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 55 

struct node {
    char letra[MAX];
    struct node *next;
};
struct hash_node {
    int size; 
    struct node **table;
};

struct hash_node *create_table (int size){
    struct hash_node *ht = (struct hash_node*)malloc(sizeof(struct hash_node));
    ht->size = size;
    ht->table = (struct node **) malloc(size *sizeof(struct hash_node));

    for (int i = 0; i < size ; i++){
        ht->table[i] = NULL ;
    }
    return ht;
}

void put (struct hash_node *ht, int h, const char *letra){
    struct node *new_node = (struct node*) malloc(sizeof(struct node));
    strcpy(new_node->letra,letra);
    new_node->next = ht->table[h];
    ht->table[h] = new_node;
}

int calculo_do_alpha(struct hash_node *ht){
    int total = 0;

    for(int i = 0; i < ht->size; i++){
        struct node *current = ht->table[i];
        while (current){
            int tam = strlen(current->letra);
            for (int j = 0; j < tam; j++){
                int x = current->letra[j] - 'A';
                total += x + i + j;
            }
            current = current->next;
        }
    }
    return total;
}
int main (){

    int n; 
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        int size; 
        scanf("%d", &size);

        struct hash_node *ht = create_table(size);

        char entrada[MAX];
        for(int i = 0; i < size; i++){
            scanf("%s", entrada);
            put(ht, i, entrada);
        }

        int result = calculo_do_alpha(ht);
        printf("%d\n", result);

        free(ht);
    }
    return 0; 
}
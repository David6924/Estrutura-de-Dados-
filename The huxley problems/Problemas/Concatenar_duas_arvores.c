#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
struct binary_tree {
    int item; 
    struct binary_tree *left;
    struct binary_tree *right;
};
struct binary_tree* create_empty_binary_tree(){
    return NULL;
}
struct binary_tree* create_binary_tree(int item){
    struct binary_tree *new_binary_tree = (struct binary_tree*)malloc(sizeof(struct binary_tree));
    new_binary_tree->item = item;
    new_binary_tree->left = NULL;
    new_binary_tree->right = NULL;
    return new_binary_tree;
}
struct binary_tree *entrada(const char* str, int *i){
    if (str[*i] == '\0'){
        return NULL;
    }
    if (str[*i] == '('){
        (*i)++;
        if (str[*i] == ')'){
            (*i)++;
            return NULL;
        }
        int sinal = 1;
        if (str[*i] == '-'){
            sinal = -1;
            (*i)++;
        }

        int item = 0 ;
        while (str[*i] >= '0' && str[*i] <= '9'){
            item = item * 10 + (str[*i] - '0');
            (*i)++;
        }
        item *= sinal;

        struct binary_tree *bt = create_binary_tree(item);
        bt->left = entrada(str, i);
        bt->right = entrada(str, i);
        (*i)++;
        return bt;
    }
    return NULL;
}
void PT (struct binary_tree* bt, int p){
    if (bt == NULL){
        printf("()");
        return;
    }
    
    printf("(%d", bt->item);
    PT(bt->left, p +1);
    PT (bt->right, p +1);
    printf(")");
}
int merge (struct binary_tree *bt, struct binary_tree *nbt){
    if (bt == NULL){
        return 0;
    }
    if (bt->item == nbt->item){
        free(bt->left);
        free(bt->right);
        bt->left = nbt->left;
        bt->right = nbt->right;
        return 1;
    }
    return merge(bt->left, nbt) || merge(bt->right, nbt);
}

int main (){
    char entradaf[MAX];
    struct binary_tree *bt = NULL;

    while (fgets(entradaf, MAX, stdin)){
        entradaf[strcspn(entradaf, "\n")] = '\0';

        if (strcmp(entradaf,"()") == 0){
            break;
        }
        int i = 0;
        struct binary_tree *nbt = entrada(entradaf, &i);

        if (bt == NULL){
            bt = nbt;
        }
        else {
            merge(bt, nbt);
        }
    }
    PT(bt, 0);
    printf("\n");
    return 0 ;
}
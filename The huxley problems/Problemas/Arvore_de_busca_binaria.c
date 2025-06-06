#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

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

        int item = 0 ;
        while (str[*i] >= '0' && str[*i] <= '9'){
            item = item * 10 + (str[*i] - '0');
            (*i)++;
        }

        struct binary_tree *bt = create_binary_tree(item);
        bt->left = entrada(str, i);
        bt->right = entrada(str, i);
        (*i)++;
        return bt;
    }
    return NULL;
}
int Depp (struct binary_tree *bt, int valor, int deep){
    if (bt == NULL){
        return -1;
    }
    if (bt->item == valor){
        return deep;
    }
    int left = Depp(bt->left, valor, deep+1);
    if(left != -1){
        return left;
    }
    return Depp(bt->right, valor, deep+1);
}

int main (){
    char e [150]; 
    scanf("%s", e);
    int n; 
    int i = 0;
    scanf("%d", &n);

    struct binary_tree *bt = entrada(e, &i);
    int depp = Depp(bt, n, 0);

    if (depp != -1){
        printf("ESTA NA ARVORE\n");
        printf("%d\n", depp);
    }
    else {
        printf("NAO ESTA NA ARVORE\n");
        printf("-1\n");
    }

    return 0;
}
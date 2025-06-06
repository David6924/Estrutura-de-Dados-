#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <stdlib.h>

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
struct binary_tree *PUT (int item, struct binary_tree *bt){
    if (bt == NULL){
        return create_binary_tree(item);
    }
    if (item < bt->item){
        bt->left = PUT(item, bt->left);
    }
    else {
        bt->right = PUT(item, bt->right);
    }
    return bt;
}
void PT (struct binary_tree *bt, int p){
    if (bt == NULL){
        printf(" () ");
        return;
    }
   if (p == 0){
        printf("   ( %d ", bt->item);
   }
   else {
        printf(" ( %d ", bt->item);
    }
    PT(bt->left, p + 1);
    PT (bt->right, p+1);
    printf(") ");
}
int main (){
    struct binary_tree *bt = create_empty_binary_tree();
    int num; 

    while (scanf("%d", &num) != EOF){
        printf("\n----\n");
        printf("Adicionando %d\n", num);
        bt = PUT(num, bt);
        PT (bt, 0);
    }
    printf("\n----\n");
    return 0;
}
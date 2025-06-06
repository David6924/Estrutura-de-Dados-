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
int node_count (struct binary_tree *bt){
        if(!bt){
            return 0;
        }
        return 1 + node_count(bt->left) + node_count(bt->right);
}
int complet (struct binary_tree *bt, int lv, int height){
    if (!bt){
        return 1;
    }
    if(!bt->left && !bt->right){
        return (lv == height);
    }
    if (!bt->left || !bt->right){
        return 0 ;
    }
    return complet(bt->left, lv + 1, height) && complet(bt->right, lv+1, height);
}
int height (struct binary_tree *bt){
    if(!bt){
        return -1;
    }
    int left_h = height(bt->left);
    int rigth_h = height(bt->right);
    return 1 + (left_h > rigth_h ? left_h : rigth_h);
}
void sons(struct binary_tree *bt, int *roots, int *i){
    if (!bt){
        return;
    }
    sons(bt->left, roots, i);
    if ((bt->left && !bt->right)||(!bt->left && bt->right)){
        roots[(*i)++] = bt->item;
    }
    sons(bt->right, roots, i);
}

int main (){
    char e[10000];
    scanf("%s", e);

    int i = 0 ;
    struct binary_tree *bt = entrada(e, &i);

    int h = height(bt);
    int com = complet(bt, 0, h);

    if (com){
        printf("completa\n");
        printf("total de nos: %d\n", node_count(bt));
    }
    else {
       printf("nao completa\n");
       int roots[10000];
       int j = 0 ;
       sons(bt, roots, &j); 
       
       printf("nos com um filho: ");
       for (int k = 0; k < j; k++){
        printf("%d", roots[k]);
        if (k < j - 1){
            printf(" ");
        }
        
       }
       printf("\n");
    }
    return 0;
}
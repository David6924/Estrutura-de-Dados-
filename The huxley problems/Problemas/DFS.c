#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX_NODES 100 
# define MAX_NAME 16

typedef struct {
    char name[MAX_NAME];
    char children[MAX_NODES][MAX_NAME];
    int child_count;
} Node;

char node_names [MAX_NODES][MAX_NAME];
int total_nodes = 0;

int exist (char *name){
    for (int i = 0; i < total_nodes; i++){
        if(strcmp(node_names[i], name) == 0) return 1;
    }
    return 0;
}
void add_node (char *name){
    if (!exist(name)) {
        strcpy(node_names[total_nodes++], name);
    }
}
int get_node_index(char *name){
    for (int i = 0; i < total_nodes; i++) {
        if (strcmp(node_names[i], name) == 0) return i;
    }
    return -1;
}
int is_leaf(int node_idx, Node node[], int active[]){
    for (int i = 0; i < node[node_idx].child_count; i++) {
        char *child = node[node_idx].children[i];
        int child_idx = get_node_index(child);
        if (child_idx != -1 && active[child_idx]) {
            return 0;
        }
    }
    return 1;
}
int cmp (const void *a, const void *b){
    return strcmp((char*)a, (char*)b);
}

int main (){
    int n ;
    while (scanf("%d", &n) == 1){
        Node nodes[MAX_NODES];
        total_nodes = 0 ;

        for (int i = 0; i < MAX_NODES; i++){
            nodes[i].child_count = 0;
        }
        for (int i = 0; i < n; i++){
            char parent[MAX_NAME], child[MAX_NAME];
            scanf("%s %s", parent, child);
            add_node(parent);
            add_node(child);
            int parent_idx = get_node_index(parent);
            strcpy(nodes[parent_idx].children[nodes[parent_idx].child_count++], child);
        }

        int active[MAX_NODES];
        for (int i = 0; i < total_nodes; i++) {
            active[i] = 1;
        }
        while (1) {
            char current_leaves[MAX_NODES][MAX_NAME];
            int leaves_count = 0;
            for (int i = 0; i < total_nodes; i++) {
                if (active[i] && is_leaf(i, nodes, active)) {
                    strcpy(current_leaves[leaves_count++], node_names[i]);
                }
            }

            if (leaves_count == 0) break;

            qsort(current_leaves, leaves_count, sizeof(current_leaves[0]), cmp);

            for (int i = 0; i < leaves_count; i++) {
                printf("%s\n", current_leaves[i]);
                active[get_node_index(current_leaves[i])] = 0;
            }
        }
    }
    return 0 ;
}
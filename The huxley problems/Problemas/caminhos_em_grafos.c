# include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX 100
struct adj_list {
    int item;
    struct adj_list *next;
};
struct graph {
    struct adj_list *vertices [MAX];
    short visited [MAX];
};
struct adj_list *creat_adj_list(int item){
    struct adj_list *new_adj_list = (struct adj_list*)malloc(sizeof(struct adj_list));
    new_adj_list->item = item;
    new_adj_list->next = NULL;
    return new_adj_list;
}
struct graph *creat_graph (){
    struct graph *graph = (struct graph*) malloc(sizeof(struct graph));
    
    for (int i = 0; i <= MAX -1; i++){
        graph->vertices[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
void add_edge (struct graph *graph, int vertex1, int vertex2){
    struct adj_list *vertex = creat_adj_list(vertex2);
    vertex->next = graph->vertices[vertex1];
    graph->vertices[vertex1] = vertex;

    vertex = creat_adj_list(vertex1);
    vertex->next = graph->vertices[vertex2];
    graph->vertices[vertex2] = vertex;
}
int bfs(struct graph *graph, int source, int target){
    int queue[MAX], front = 0 , rear = 0;
   

    for (int  i = 0; i < MAX; i++){
        graph->visited[i] = 0;
        
    }

    graph->visited[source] = 1 ;
    queue[rear++] = source;

    while (front < rear)
    {
        int current = queue[front++];
        if (current == target){
            return 1;
        }
        struct  adj_list *adj = graph->vertices[current];
        while (adj != NULL){
            int neighbor = adj->item;
            if (!graph->visited[neighbor]){
                graph->visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
            adj = adj->next;
        }
    }
    return 0 ;
    
}
int main (){
    int V; 
    int A; 
    scanf("%d %d", &V, &A);

    struct graph *graph = creat_graph();

    for (int i = 0; i < A; i++){
        int V1i , V2i;
        scanf("%d %d", &V1i, &V2i);
        add_edge(graph, V1i, V2i);
    }

    int S, E ;
    scanf("%d %d", &S, &E);

    int breth_first = bfs(graph, S, E);

    if (breth_first == 1){
        printf("EXISTE\n");
    }
    else {
    printf("NAO EXISTE\n");
    }
    return 0;
}
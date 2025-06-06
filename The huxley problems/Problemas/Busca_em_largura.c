#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 

typedef struct {
    int adj[MAX][MAX];
    int vertices;
    int arestas;
}Grafo;

typedef struct {
    int itens[MAX];
    int start;
    int end;
} Fila;

void init_fila(Fila *f){
    f->start = 0;
    f->end = -1 ;
}
int empty(Fila *f){
    return f->start > f->end;
}
void Put (Fila *f, int item){
    f->itens[++f->end] = item;
}
int un_put (Fila *f){
    return f->itens[f->start++];
}
void init_graph (Grafo *g, int vertices){
    g->vertices = vertices;
    g->arestas = 0;

    for (int i = 0; i < vertices; i++){
        for (int j = 0; j < vertices; j++){
            g->adj[i][j] = 0;
        }
    }
}
void add_aresta(Grafo *g, int origem, int destino){
    if (g->adj[origem][destino] == 0){
        g->adj[origem][destino] = 1 ;
        g->arestas++;
    }
}
void bfs(Grafo *g, int  origem, int destino, int caso){
    Fila fila;
    int visited[MAX] = {0};
    int distance[MAX];
    int predecessor[MAX];
    init_fila(&fila);

    for (int  i = 0; i < g->vertices; i++){
        distance[i] = -1;
        predecessor[i] = -1;
    }
    visited[origem] = 1;
    distance[origem] = 0;
    Put(&fila, origem);

    printf("\nCaso de Teste #%d - BFS(%d)\n\n", caso, origem);

    while (!empty(&fila)){
        int current = un_put(&fila);

        printf("Iniciando busca em largura a partir de %d\n", current);

        for (int i = 0; i <g->vertices; i++){
            if (g->adj[current][i] == 1 && !visited[i]){
                visited[i] = 1;
                distance[i] = distance[current] + 1;
                predecessor[i] = current;
                Put(&fila, i);
            }
        }
    }
    printf("\n");
    for (int  i = 0; i < g->vertices; i++){
        printf ("%d | ", i);

        if (distance[i] == -1){
            printf("- | -\n");
        }
        else {
            printf("%d | ", distance[i]);
            if (predecessor[i] == -1){
                printf("-\n");
            }
            else {
                printf("%d\n", predecessor[i]);
            }
        }
    }

    if (distance[destino] == -1){
        printf("\nSem caminho entre %d e %d\n", origem, destino);
    }
    else {
        int way[MAX];
        int tam_way = 0;
        int current = destino;

        while (current != origem){
            way[tam_way++] = current;
            current = predecessor[current];
        }
        way[tam_way] = origem;

        printf("\nCaminho entre %d e %d: ", origem, destino);
        printf("%d", way[tam_way]);

        for (int  i = tam_way -1; i >= 0; i--){
            printf(" => %d", way[i]);
        }
        printf("\n");
    }
}
int main (){
    Grafo grafo;
    int vertices, arestas, casos;

    scanf("%d %d %d", &vertices, &arestas, &casos);

    init_graph(&grafo, vertices);

    for (int i = 0; i < arestas; i++){
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        add_aresta(&grafo, origem, destino);
    }
    for (int i = 0; i < casos; i++){
        int origem,  destino;
        scanf("%d %d", &origem, &destino);
        
        if (i > 0) {
            printf("\n--------\n");
        } else {
            printf("--------\n");
        }
        
        bfs(&grafo, origem, destino, i + 1);
        
        if (i == casos - 1) {
            printf("\n--------\n");
        }
    }
    return 0;
}
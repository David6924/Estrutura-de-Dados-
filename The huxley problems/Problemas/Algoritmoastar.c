/* A* com obstáculos e custos de terreno
 * Compile:  gcc -std=c99 -Wall -O2 a_star.c -o a_star
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>   // INT_MAX
#include <math.h>

#define WIDTH  5
#define HEIGHT 5
#define MAX_NODES (WIDTH * HEIGHT)

/* ---------- mapa de terreno e obstáculos ---------- */
/* Custo de entrar na célula (1 = terreno normal, >1 = mais caro) */
int terrain[HEIGHT][WIDTH] = {
/* y=0 */ {1, 1, 1, 1, 1},
/* y=1 */ {1, 4, 4, 1, 1},
/* y=2 */ {1, 4, 1, 1, 1},
/* y=3 */ {1, 1, 1, 3, 3},
/* y=4 */ {1, 1, 1, 1, 1},
};

/* 1 = obstáculo (muro), 0 = livre */
int wall[HEIGHT][WIDTH] = {
/* y=0 */ {0, 1, 0, 0, 0},
/* y=1 */ {0, 1, 0, 0, 0},
/* y=2 */ {0, 1, 0, 0, 0},
/* y=3 */ {0, 1, 0, 0, 0},
/* y=4 */ {0, 0, 0, 0, 0},
};
/* ---------- fim do mapa ---------- */

typedef struct Node {
    int x, y;               /* coordenadas */
    int g, h, f;            /* g = custo origem->nó; h = heurística; f = g+h */
    int cost;               /* custo de entrar nesta célula (terrain) */
    struct Node *parent;    /* caminho */
    int in_open, in_closed;
} Node;

/* Manhattan admissível se custo mínimo = 1 */
static inline int heuristic(Node *a, Node *b) {
    return (abs(a->x - b->x) + abs(a->y - b->y));
}

/* custo da aresta = custo de entrar no vizinho */
static inline int distance(Node *from, Node *to) {
    return to->cost;
}

/* imprime caminho de goal até start */
void reconstruct_path(Node *current) {
    printf("Caminho encontrado:\n");
    while (current) {
        printf("(%d,%d) ", current->x, current->y);
        current = current->parent;
        if (current) printf("<- ");
    }
    printf("\n");
}

void A_Star(Node *start, Node *goal, Node nodes[HEIGHT][WIDTH]) {
    Node *open[MAX_NODES];
    int openCount = 0;

    start->g = 0;
    start->h = heuristic(start, goal);
    start->f = start->h;
    start->in_open = 1;
    open[openCount++] = start;

    /* deslocamentos ortogonais (adicione diagonais se quiser) */
    const int dx[] = { 0, 1, 0,-1};
    const int dy[] = {-1, 0, 1, 0};

    while (openCount) {
        /* extrai nó com menor f (fila não ordenada) */
        int best = 0;
        for (int i = 1; i < openCount; ++i)
            if (open[i]->f < open[best]->f) best = i;

        Node *current = open[best];

        /* chegou ao destino */
        if (current == goal) {
            reconstruct_path(current);
            return;
        }

        /* remove current da open list */
        open[best] = open[--openCount];
        current->in_open = 0;
        current->in_closed = 1;

        /* explora vizinhos */
        for (int d = 0; d < 4; ++d) {
            int nx = current->x + dx[d];
            int ny = current->y + dy[d];

            if (nx < 0 || ny < 0 || nx >= WIDTH || ny >= HEIGHT) continue;

            Node *nbr = &nodes[ny][nx];
            if (nbr->in_closed) continue;

            int tentative_g = current->g + distance(current, nbr);
            if (!nbr->in_open) {              /* descobre novo nó */
                open[openCount++] = nbr;
                nbr->in_open = 1;
            } else if (tentative_g >= nbr->g) { /* não é melhor */
                continue;
            }

            /* melhor caminho até aqui */
            nbr->parent = current;
            nbr->g = tentative_g;
            nbr->h = heuristic(nbr, goal);
            nbr->f = nbr->g + nbr->h;
        }
    }
    puts("Nenhum caminho encontrado.");
}

int main(void) {
    Node nodes[HEIGHT][WIDTH] = {0};

    /* inicializa nós */
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x) {
            Node *n = &nodes[y][x];
            n->x = x; n->y = y;
            n->g = INT_MAX/2; n->f = INT_MAX/2;
            n->cost = terrain[y][x];
            n->in_open = n->in_closed = 0;
            n->parent = NULL;
            if (wall[y][x]) n->in_closed = 1;     /* obstáculo */
        }

    Node *start = &nodes[0][0];
    Node *goal  = &nodes[4][4];

    A_Star(start, goal, nodes);
    return 0;
}

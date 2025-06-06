#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct deque {
    ITEM vet[TAM];
    int front, rear;
} TDeque;

void create(TDeque *d) {
	d->front = 0 ; 
    d->rear = 0;
}

void destroy(TDeque *d) {
	d->front = d->rear ; 
}

int isfull(TDeque *d) {
	return d->rear == TAM ;
}

int isempty(TDeque *d) {
	return d->front == d->rear ;
}

void store(TDeque *d, int extremidade, ITEM x) {
	if (isfull(d)){
        abort();
    }
    if (extremidade == 1){
        for(int i = d->rear; i >0; i--){
            d->vet[i] = d->vet[i-1];
        }
        d->vet[0] = x ; 
        d->rear++;
    }
    else if (extremidade == 2){
        d->vet[d->rear] = x ;
        d->rear++; 
    }
}

ITEM retrieve(TDeque *d, int extremidade) {
	if (isempty(d)){
        abort();
    }
    ITEM temp ; 

    if (extremidade == 1){
        temp = d->vet[0];
        for (int i = 0; i < d->rear - 1; i++){
            d->vet[i] = d->vet[i+1];
        }
        d->rear--;
    }
    else if (extremidade == 2){
        d->rear -- ; 
        temp = d->vet[d->rear];
    }
    return temp;
}

void preenche(TDeque *d) {
    ITEM x;
    int qtd, extremidade, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &extremidade);
        store(d, extremidade, x);
    }
}

void exibe(TDeque *d) {
    int extremidade;

    while( scanf("%d", &extremidade) != EOF ) {
		if( extremidade==1 )
        	printf("INICIO = %c\n", retrieve(d, extremidade));
		else
			printf("FIM = %c\n", retrieve(d, extremidade));
	}
}

int main(void) {
    TDeque d;

    create(&d);
    preenche(&d);
    exibe(&d);
    destroy(&d);

    return 0;
}

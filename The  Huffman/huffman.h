#include "structs.h" // Chama as structs

unsigned long tamanho_arquivo(FILE *arquivo_entrada){
    if (!arquivo_entrada) return -1;

    fseek(arquivo_entrada, 0, SEEK_END); // Move 0 byts a partir do início o ponteiro de posição de leitura para o final do aquivo
    unsigned long tam_arq = ftell(arquivo_entrada); // Retorna a posição atual, ou seja o tamanho
    rewind(arquivo_entrada); // Volta o ponteiro para o início
    return tam_arq; // Retorna o tamanho do arquivo
}

unsigned long *contar_frequencia(FILE *arquivo_entrada, unsigned long tam_arq){
    unsigned long *frequencia = (unsigned long*)calloc(TAM_ASCII, sizeof(unsigned long)); // Aloca memória igual ao malloc, só que ao invés de deixar lixo de memória ela alcoa tudo com zero
    unsigned char byte;                // Num de elementos a serem alocados | numero de bytes de cada elemento

    for (int i = 0 ; i < tam_arq; i++){
        fread(&byte, sizeof(unsigned char), 1 , arquivo_entrada); // fread ler dados binários de um arquivo para a memória
        // bloco de memório onde os arquivos vão ser amarzenados | Tam de cada elemento | num de elementos a serem lidos | ponteiro para o arquivo
        frequencia[byte]++;
    }

    rewind(arquivo_entrada); //Volta o ponteiro para o início
    return frequencia; 
}

void inserir_ordenado(LISTA *fila, NOHUFF *novo){
    if(fila->inicio == NULL || novo->frequencia <= fila->inicio->frequencia){ // Caso não tenho nenhum elemento na fila ou o primeiro elemento da fila tiver uma frequência maior ou igual a frequencia do novo NOHUFF
        novo->prox = fila->inicio; // swap
        fila->inicio = novo; // swap
    }
    else{
        NOHUFF *aux = fila->inicio; // No auxiliar que aponta para o primeiro elemento 
        while (aux->prox && aux->prox->frequencia < novo->frequencia){
            aux = aux->prox; // swap
        }
        novo->prox = aux->prox; // swap
        aux->prox = novo; // swap
    }
    fila->tamanho++; // aumenta o tamanho da heap
}

void preencher_fila(unsigned long *frequencia, LISTA *lista){ // Cria uma no para cada letra
    NOHUFF *novo; // Cria uma novo no
    for(int i = 0; i < TAM_ASCII; i++){
        if(frequencia[i] > 0){ // Se a letra tiver 1 ou mais repretições
            novo = (NOHUFF*)malloc(sizeof(NOHUFF)); // Aloca memória para o NOHUFF

            novo->caracter = malloc(sizeof(unsigned char)); // Aloca memória para a letra
            *(unsigned char*) novo->caracter = i; // Armazena o código do caractere em ASCII
            novo->frequencia = frequencia[i]; // Diz quantas vezes os caractere se repetiu
            novo->direita = NULL;
            novo->esquerda = NULL;
            novo->prox = NULL;

            inserir_ordenado(lista, novo);
        }
    }
}
NOHUFF *remove_no_inicio(LISTA *fila){ // Remove o caracter com menor frequencia da lista que se encontra no início
    NOHUFF *aux = NULL;

    if (fila->inicio){
        aux = fila->inicio;
        fila->inicio = aux->prox; // Move o ponteiro inicio da lista para o segundo nó. Isso efetivamente remove o primeiro nó da lista 
        aux->prox = NULL;
        fila->tamanho--;
    }

    return aux; // Retorna o nó que foi removido. Vai servir para montar a arvore huff
}
NOHUFF *montar_arvore(LISTA *fila){
    NOHUFF *primeiro, *segundo, *novo;
    while(fila->tamanho > 1){ // Se ouver mais de um nó a fila ainda é possível combinar dois
    // O ultimo nó será a raiz da árvore huffman 
        primeiro = remove_no_inicio(fila); // remove o primero 1° nó
        segundo = remove_no_inicio(fila); // Em sequência remove o 2° nó

        novo = (NOHUFF*)malloc(sizeof(NOHUFF)); // Cria um novo nó
        novo->caracter = malloc(sizeof(unsigned char)); // aloca memória para os caracteres
        *(unsigned char*)novo->caracter = '*'; // MArcador de nó interno da arvore
        novo->frequencia = primeiro->frequencia + segundo->frequencia; // Junta a frequência dos dois nós
        novo->esquerda = primeiro;
        novo->direita = segundo;
        novo->prox = NULL;

        inserir_ordenado(fila, novo);
    }

    return fila->inicio;
}
// Retorna a altura da arvore
unsigned int altura_arvore (NOHUFF *raiz){
    if(!raiz) return -1; // Se não tiver raiz acaba a função

    int esq = altura_arvore(raiz->esquerda) + 1;
    int dir = altura_arvore(raiz->direita) + 1;

    return (esq > dir) ? esq : dir; // Retorna o maior valor entre a direita e a esquerda
}

void gerar_dicionario(unsigned char **dicionario, NOHUFF *raiz, char *caminho, unsigned int tam_max){
    char esquerda[tam_max], direita[tam_max];

    if(!raiz->esquerda && !raiz->direita) // Se o nó não tiver filhos ele é uma folha
        strcpy((char*)dicionario[*(unsigned char*)raiz->caracter], caminho); // Diz um caractere e copia o caminho até a folha do dicionário
    else{
        strcpy(esquerda, caminho); // Copia o caminho para a esquerda
        strcpy(direita, caminho); // Copia para a direita

        strcat(esquerda, "0"); // adiciona  0  ao caminho da esquerda // gera o código do dicionário
        strcat(direita, "1"); // adiciona 1 ao caminho da direita

        gerar_dicionario(dicionario, raiz->esquerda, esquerda, tam_max); // passo recursivo
        gerar_dicionario(dicionario, raiz->direita, direita, tam_max); // passo recursivo
    }
}

// Marcelo explicou
short salvar_arvore(NOHUFF *raiz, FILE *arquivo_saida){
    if(!raiz) return 0;
    
    int folha_escape = (*(unsigned char*)raiz->caracter == '*' || *(unsigned char*)raiz->caracter == '\\') && !raiz->esquerda && !raiz->direita;

    if(folha_escape)
        fwrite("\\", sizeof(unsigned char), 1, arquivo_saida);
    
    fwrite(&*(unsigned char*)raiz->caracter, sizeof(unsigned char), 1, arquivo_saida);
    int esquerda = salvar_arvore(raiz->esquerda, arquivo_saida);
    int direita = salvar_arvore(raiz->direita, arquivo_saida);
    
    return 1 + esquerda + direita + folha_escape;
}

short salvar_dados(FILE *arquivo_entrada, FILE *arquivo_saida, unsigned char **dicionario, int tam_arquivo, int tam_arvore){
    int bit_atual = 0;
    int tamanho_lixo = 0;
    unsigned char escrever_buffer = 0;
    unsigned char ler_buffer;

    fseek(arquivo_saida, 0, SEEK_END);

    for (int i = 0; i < tam_arquivo; i++){
        fread(&ler_buffer, sizeof(unsigned char), 1, arquivo_entrada);
        unsigned char *codigo = dicionario[ler_buffer];

        for(int j = 0; codigo[j] != '\0'; j++){
            escrever_buffer <<= 1;
            if(codigo[j] == '1')
                escrever_buffer |= 1;
            
            bit_atual++;

            if(bit_atual == 8){
                fwrite(&escrever_buffer, sizeof(unsigned char), 1, arquivo_saida);
                escrever_buffer = 0;
                bit_atual = 0;
            }
        }
    }

    if(bit_atual > 0){
        escrever_buffer <<= 8 - bit_atual;
        fwrite(&escrever_buffer, sizeof(unsigned char), 1, arquivo_saida);
        tamanho_lixo = 8 - bit_atual;
    }

    fclose(arquivo_entrada);
    rewind(arquivo_saida);
    return tamanho_lixo;
}
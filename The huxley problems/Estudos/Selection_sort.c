#include <stdio.h>

// Função para trocar dois elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int s[], int n) {
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (s[j] < s[min]) {
                min = j;
            }
        }
        swap(&s[i], &s[min]);
    }
}

int main() {
    int n;
    printf("Digite o número de elementos: ");
    scanf("%d", &n);
    int s[n];

    printf("Digite os elementos:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }

    selection_sort(s, n);

    printf("Array ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", s[i]);
    }
    printf("\n");

    return 0;
}
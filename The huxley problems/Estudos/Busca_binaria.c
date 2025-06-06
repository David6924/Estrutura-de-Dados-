#include <stdio.h>
int binary_search(int *v, int size, int element)
{
    int begin = 0;
    int end = size – 1;
    int middle;

    while (begin <= end) {
        middle = (begin + end) / 2;
        if (v[middle] < element) {
            begin = middle + 1;
        } else if (v[middle] > element) {
            end = middle - 1;
        } else {
            return middle;
        }
 }
        return -1;
}
int main (){

    int v [10] = {1,2,3,4,5,6,7} ; 

    int size = sizeof (v) / sizeof(v[0]) ; 

    // O algoritmo de busca binária só pode ser usada em arrays ordenados  
    // Devemos saber o início e o fim do nosso vetor 
    // Meio = (início + fim ) / 2 
    /* Caso o elemento não desejado não esteja no meio
        - início  = Meio + 1 ;  (if array[Meio] < elemento )
        - end = Meio - 1  ; (if  array[Meio] > elemento )
    
    */ 
    return 0 ; 
}
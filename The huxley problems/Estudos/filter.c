#include <stdio.h> 
int impar(int x){
    return x % 2 != 0 ;   // Volta um valor booleano ; 1 se for impar 0  se for par  
}
int par (int x){
    return x % 2 == 0 ; 
}

void filter(int *array, int (*impar)(int), int size){
    printf ("*** E impar ***\n");
    for (int i = 0 ; i < size ; i++){
       if (impar(array[i])){ // Recebe o valor booleano 
            printf ("%d\n", array[i]);
       }
    }
}
void filter_2(int *array , int (*par)(int), int size){
    printf ("*** E par ***\n");
    for (int i = 0 ; i < size ; i++){
        if (par(array[i])){
            printf ("%d\n", array[i]);
        }
    }
}
int main (){

    int array [8] = {6 , 12, 28 , 7 ,99 , 57 , 666 , 333};

    int size = sizeof (array) / sizeof (array[0]) ;

    filter (array , impar, size);
    filter_2 (array, par , size);

    return 0 ; 
}
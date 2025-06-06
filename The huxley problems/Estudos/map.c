#include <stdio.h>
int square (int x){
    return x * x ;
}

void Map(int *array , int (*square)(int),  int size ){
    for (int i = 0 ; i < size; i++){
        array[i] = (*square)(array[i]) ; 
        printf ("%d\n", array[i]);
    }
}
int main (){
    int array [5] = {1 , 2 , 3 , 4, 5} ; 
    int size = sizeof (array) / sizeof (array[0]);

    for (int i = 0 ; i < size ; i++){
        printf ("%d\n", array[i]);
        if (i == size-1){
            printf ("-------------***-------------\n");
        }
    }
    
   
    Map (array , square, size);

    return 0 ; 
}
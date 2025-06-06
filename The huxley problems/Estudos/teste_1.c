#include <stdio.h>
void Teste (int n){
    if (n > 0) {
        for (int i = 1 ; i < n ; i = i * 2){
            printf ("%d ",i);
        }
        Teste (n - 1);
    }
}
int main (){
    int n ; 
    scanf ("%d", &n);

    Teste (n);
    return 0 ; 
}
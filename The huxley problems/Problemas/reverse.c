int reverse_num(int num){
    
    int reverse_num = 0 ; 
    while (num != 0){
        int digit = num % 10 ; 
        reverse_num = reverse_num * 10 + digit ; 
        num = num / 10;
    }
    return reverse_num ;
}
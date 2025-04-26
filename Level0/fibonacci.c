#include <stdio.h>
#include <stdlib.h>

// prototypes
int fib(int n);

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ./fibonacci n\n");
        return 1;
    }else if(atoi(argv[1]) <= 0){
        printf("Pick a positive nuber\n");
        return 1;
    }

    const int N = atoi(argv[1]);

    for(int i=1; i<=N; i++){
        printf("%d, ", fib(i));
    }

    printf("\n");

}

int fib(int n){
    // give us the nth fib number from the fib seq.

    if(n < 2){
        // base cause
        return n;
        
    }else{
        // recursive
        return fib(n-1) + fib(n-2);
    }

}

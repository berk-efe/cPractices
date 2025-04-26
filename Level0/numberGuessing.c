#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void){

    srand(time(NULL));
    const int RAND_NUM = rand() % 100 + 1;

    int number;
    bool found = false;
    while(!found){
        printf("Guess: ");
        scanf("%d", &number);

        if(number < RAND_NUM){
            printf("Too low.\n");
        }else if(number > RAND_NUM){
            printf("Too high.\n");
        }else{
            printf("Found!");
            return 0;
        }
    }

    return 0;

}
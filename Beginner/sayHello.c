#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc > 0){
        printf("Hello, ");
        for(int i=1; i<argc; i++){
            printf("%s ", argv[i]);
        }
        printf("\n");

    }else{
        printf("Hello World\n");
        return 0;
    }

}


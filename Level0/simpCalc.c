#include <stdio.h>


int main(void){
    printf("1: +\n2: -\n3: *\n4: /\n");
    
    int op = 0;
    printf("Pick the operator: ");
    scanf("%d", &op);
    while (op > 4 || op < 1){
        printf("Pick the operator: ");
        scanf("%d", &op);
    }
    
    int first_num;
    printf("First number: ");
    scanf("%d", &first_num);
    

    int sec_num;
    printf("Second number: ");
    scanf("%d", &sec_num);

    switch(op){
        case 1:
            printf("%d\n", first_num + sec_num);
        case 2:
            printf("%d\n", first_num - sec_num);
        case 3:
            printf("%d\n", first_num * sec_num);
        case 4:
            if (sec_num == 0){
                printf("Cannot divide with 0\n");
                return 1;
            }
            printf("%.2f\n", (float)first_num / (float)sec_num);
    }

    return 0;

}
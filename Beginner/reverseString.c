#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char str[256];
    printf("String: ");
    scanf("%[^\n]s", str);
    printf("%s\n", str);

    int str_len = strlen(str);

    char *reversed_str = malloc(sizeof(char) * str_len);
    for (int i=0; i<str_len; i++){
        reversed_str[i] = str[str_len - i - 1];
    }

    printf("%s\n", reversed_str);

    return 0;

}
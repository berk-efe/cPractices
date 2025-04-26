#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *reverseStr(char* str){
    int str_len = strlen(str);
    
    char *reversed_str = malloc(sizeof(char) * str_len+1);
    for (int i=0; i<str_len; i++){
        reversed_str[i] = str[str_len - i - 1];
    }
    
    return reversed_str;
}

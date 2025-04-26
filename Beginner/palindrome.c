#include <stdio.h>
#include <string.h>

#include "reverseString.h"

int main(void){
    char str[256];
    printf("String: ");
    scanf("%[^\n]s", str);

    char *reversed_str = reverseStr(str);

    // case-insensitive comparison
    if(strcasecmp(str, reversed_str) == 0){
        printf("Palindrome.\n");
        return 0;
    }else {
        printf("Not Palindrome.\n");
        return 0;
    }

}
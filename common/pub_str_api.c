#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char*
replace_string(char* str, char* a, char* b)
{
    int len  = strlen(str);
    int lena = strlen(a);
    int lenb = strlen(b);
    char* p = NULL;

    for (p = str; p = strstr(p, a), p != NULL; ++p) {
        if (lena != lenb) {
            memmove(p+lenb, p+lena, len - (p - str) + lenb);
        }
        memcpy(p, b, lenb);
    }
    return str;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char*
replace_string(char* str, char* a, char* b)
{
    int len  = strlen(str);
    int lena = strlen(a);
    int lenb = strlen(b);
    char* p = NULL;

    for (p = str; p = strstr(p, a), p != NULL; ++p) {
        if (lena != lenb) {
            memmove(p+lenb, p+lena, len - (p - str) + lenb);
        }
        memcpy(p, b, lenb);
    }
    return str;
}


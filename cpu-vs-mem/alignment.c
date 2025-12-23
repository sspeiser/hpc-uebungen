#include <stdio.h>

struct triple {
    char r;
    char g;
    char b;
};

struct triple t1;
struct triple t2;



int main() {

    char* addr1 = (char *) &t1;
    char* addr2 = (char *) &t2;

    printf("%ld memory addresses difference\n", addr2 - addr1);    


}
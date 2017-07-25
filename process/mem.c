#include <stdio.h>
#include <stdlib.h>

int x1=1 ;
int x2 ;

extern int etext, edata, end;

int main(int argc, char *argv[], char *envp[]) {
    int x3;
    char *x4p;

    printf("&main == 0x%x \n", &main );
    printf("&etext == 0x%x \n",&etext );
    printf("&edata == 0x%x \n",&edata );
    printf("&end   == 0x%x \n",&end );

    printf("&x1 == 0x%x (data)\n",&x1 );
    printf("&x2 == 0x%x (bss)\n", &x2 );
    printf("&x3 == 0x%x (auto)\n",&x3 );
    x4p = malloc( 10 );
    printf("x4p == 0x%x (heap)\n",x4p );
    x4p = malloc( 10 );
    printf("x4p == 0x%x (heap)\n",x4p );
    recursive( 3 );
}

void recursive(int n) {
    int x5 ;
    printf("&x5 == 0x%x (auto,%d)\n",&x5,n );
    if( n<=0 )
        return;
    recursive( n-1 );
}

#include <stdio.h>

typedef struct{
    int primo_elemento;
    int secondo_elemento;
} mia_struttura;

void f(mia_struttura * puntatore){
    (*puntatore).primo_elemento=(*puntatore).primo_elemento+15;
}

int main()
{
    mia_struttura x,y;
    
    x.primo_elemento=3;
    x.secondo_elemento=5;

    y.primo_elemento=6;
    y.secondo_elemento=10;
    
    f(&y);

    printf("Hello, World!\n%d, %d\n",y.primo_elemento,y.secondo_elemento);
    
    return 0;
}

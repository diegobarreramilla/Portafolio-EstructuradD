#include <stdio.h>
#include <stdlib.h>
#include "funcionesP4.h"

int main(void)
{
    unsigned char **lab; 
    
    lab = crear_laberinto();    
    imprimirLab(lab);   
    
    lab[9][1] ='B';
    
    
    resolver(lab);             
    
    imprimirLab(lab);           
    printf("\n\n");

    return 0;
}

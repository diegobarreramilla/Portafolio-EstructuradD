#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

int main(void){

    Pila pila = inicializarPila(50);
    pila.imprimir = imprimirEntero;
    int opc;

   
    do {
        printf("\n[1] Pasar de Infix a postfix: \n");
        printf("\n[2] Salir\n");
        scanf("%i",&opc);
        getchar();

        switch (opc)
        {
        case 1:{
        /////comprobar si si es
        char arreglo[100];
            printf("Introduza en infix: \n");
            fgets(arreglo,sizeof(arreglo),stdin);

        int tamano = strlen(arreglo);

        eliminarSalto(arreglo,tamano);

        char *arr = malloc((tamano+1) *sizeof(char));
        strcpy(arr,arreglo);

        ///arreglo final
        char *postfix = malloc((tamano+1) * sizeof(char));
        conversion(arr, postfix, &pila);
        imprimirArreglo(postfix);


            
            break;
        }
        default:
            break;
        }

        
    }while(opc != 2);
    





    return 0;
} 

void imprimirEntero(void *dato) {
    printf("%d", *(int*)dato);
}

void eliminarSalto(char *arreglo,int tamano){

    if(arreglo[tamano-1] == '\n' && tamano>0){
        arreglo[tamano-1] = '\0';
    }


}
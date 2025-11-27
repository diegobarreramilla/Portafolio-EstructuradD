#include <stdio.h>
#include <string.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

void verificarPalindromo();
void verificarParentesis();

int main() {
    int opcion;
    do {
        
        printf("\n1 Palindromo\n");
        printf("2 Verificacion de parentesis\n");
        printf("3 Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch(opcion) {
            case 1: verificarPalindromo();
			 break;
            case 2: verificarParentesis(); 
			break;
            case 3: printf("Saliendo\n"); 
			break;
            default: printf("Opcion invalida\n");
        }
    } while(opcion != 3);

    return 0;
}

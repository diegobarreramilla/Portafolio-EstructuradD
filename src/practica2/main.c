#include <stdio.h>

#include "../Estructuras/listadoble/listadoble.h"
#include "../captura/captura.h"

#define LONGITUD 5

int main(void)
{
	ListaD lista;
	lista = inicializarListaD();
	mostrarListaD(lista);
	int x;
	char cadena[LONGITUD];
	
	inputEntero("\n Captura x: ",&x);
	inputCadena("\n Captura nombre: ",cadena,LONGITUD); 
	inputEntero("\n Captura x: ",&x);
	inputCadena("\n Captura nombre: ",cadena,LONGITUD); 
	inputEntero("\n Captura x: ",&x);
	inputCadena("\n Captura nombre: ",cadena,LONGITUD); 
	
	printf("\n %d %s",x,cadena);
	printf("\n %d %s",x,cadena);
	return 0;
}


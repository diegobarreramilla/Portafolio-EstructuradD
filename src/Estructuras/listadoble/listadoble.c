#include "listadoble.h"
#include <stdio.h>


ListaD inicializarListaD(void)
{
	return (ListaD) {NULL,NULL,0,NULL,NULL,NULL};
}
void mostrarListaD(ListaD lista)
{
	NodoD *p;	
	printf("\n Lista[%d]: ",lista.cant);
	for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
	{
		printf(" ");
		lista.imprimir(p->dato);
		printf("->");
	}
	printf("NULL");
}
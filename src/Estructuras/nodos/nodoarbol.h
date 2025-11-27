#ifndef NODO_ARBOL
#define NODO_ARBOL
#include <stdlib.h>

typedef struct nodoA
{
	struct nodoA *izq;
	struct nodoA *dch;
	void *dato;
}NodoA;

NodoA* crearNodoA(void *dato);

#endif
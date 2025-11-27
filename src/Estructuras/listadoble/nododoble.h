#ifndef NODO_DOBLE_H
#define NODO_DOBLE_H


#include <stdlib.h>

typedef struct nodo
{
	void *dato;
	struct nodo *sig;
	struct nodo *ant;
}NodoD;

NodoD* crearNodoD(void *dato);

#endif
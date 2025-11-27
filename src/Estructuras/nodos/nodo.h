#ifndef NODO_H
#define NODO_H

#include <stdlib.h>

typedef struct nodo
{
	void *dato;
	struct nodo *sig;
	
}Nodo;

Nodo* crearNodo(void*);

#endif
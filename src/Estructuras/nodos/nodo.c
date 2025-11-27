#include "Nodo.h"


Nodo* crearNodo(void* dato)
{
	Nodo *nuevo = calloc(1,sizeof(Nodo));
	nuevo->dato = dato;
	return nuevo;
}
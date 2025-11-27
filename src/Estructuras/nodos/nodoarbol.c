#include "nodoarbol.h"


NodoA* crearNodoA(void *dato)
{
	NodoA *nuevo = calloc(1,sizeof(NodoA));
	nuevo->dato = dato;
	return nuevo;
}
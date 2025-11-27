#include "nododoble.h"


NodoD* crearNodoD(void *dato)
{
	NodoD *nuevo = (NodoD*) calloc(1,sizeof(NodoD));
	nuevo->dato = dato;
	return nuevo;
}
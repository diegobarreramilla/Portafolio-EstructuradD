#ifndef COLA_H
#define COLA_H

#include "../nodos/nodo.h"

typedef struct
{
	Nodo *inicio;
	Nodo *fin;
	int capacidad;
	int cantidad;
	void (*imprimir)(void*); //SE ASIGNA LA FUNCION PARA IMPRIMIR LOS DATOS
	void (*liberar)(void*); //SE ASIGNA LA FUNCION PARA LIBERAR DATOS,SI SE NECESITA
}Cola;

Cola inicializarCola(void);
int llenaC(Cola cola);
int vaciaC(Cola cola);
void enqueue(Cola *cola,void *dato); //AGREGAR UN ELEMENTO
void* peekC(Cola cola); //CONSULTA
void* dequeue(Cola *cola); //ELIMINA
void imprimirCola(Cola cola);
void eliminarCola(Cola *cola);

void* buscarC(Cola cola,void *dato,int (*comparar)(void*,void*));


////
void Escanear(Cola *cola );

#endif



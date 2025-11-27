#include "cola.h"
#include <stdio.h>

Cola inicializarCola(void)
{
	return (Cola) {NULL,NULL,-1,0,NULL,NULL};
}

/*Cola inicializarCola(int capacidad)
{
	return (Cola) {NULL,NULL,capacidad,0,NULL,NULL};
}
*/
int llenaC(Cola cola)
{
	return cola.capacidad==cola.cantidad;
}

int vaciaC(Cola cola)
{	
	return (cola.inicio==NULL && cola.cantidad==0);
}

void enqueue(Cola *cola,void *dato)
{	
	if(llenaC(*cola))return;//OVERFLOW
	Nodo *nodo = crearNodo(dato);
	if(vaciaC(*cola))
		cola->inicio = cola->fin = nodo;
	else
	{
		cola->fin->sig = nodo;
		cola->fin = nodo;
	}
	cola->cantidad++;	
}
void* peekC(Cola cola)
{	
	if(vaciaC(cola))	return NULL;
	return cola.inicio->dato;
}

void* dequeue(Cola *cola)
{	
	if(vaciaC(*cola)) return NULL; //UNDERFLOW
	Nodo *aux;
	aux = cola->inicio;
	cola->inicio = aux->sig ; 
	aux->sig = NULL;
	if(cola->inicio == NULL) cola->fin = NULL;
	cola->cantidad--;
	void *dato = aux->dato;
	free(aux);
	return dato;
}

void enqueue_Nodo(Cola *cola,Nodo* nodo)
{	
	if(llenaC(*cola))return;//OVERFLOW
	if(vaciaC(*cola))
		cola->inicio = cola->fin = nodo;
	else
	{
		cola->fin->sig = nodo;
		cola->fin = nodo;
	}
	cola->cantidad++;	
}

Nodo* dequeue_Nodo(Cola *cola)
{	
	if(vaciaC(*cola)) return NULL; //UNDERFLOW
	Nodo *aux;
	aux = cola->inicio;
	cola->inicio = aux->sig ; 
	aux->sig = NULL;
	if(cola->inicio == NULL) cola->fin = NULL;
	cola->cantidad--;
	return aux;
}


void imprimirCola(Cola cola)
{
	for(int i = 0; i < cola.cantidad ; i++)
	{
		
		cola.imprimir( peekC(cola));
		printf(" ->");
		enqueue_Nodo( &cola , dequeue_Nodo(&cola));
	}		
}

void eliminarCola(Cola *cola)
{
	return;
}

void* buscarC(Cola cola,void *dato,int (*comparar)(void*,void*))
{
	void *dato_encontrado = NULL;
    int n = cola.cantidad;

    // Usamos el "truco" de rotación para recorrer la cola sin perderla
    for (int i = 0; i < n; i++)
    {
        void *dato_actual = peekC(cola);

        // Comparamos el dato actual con el que buscamos
        if (comparar(dato_actual, dato) == 0) // 0 = son iguales
        {
            dato_encontrado = dato_actual;
        }

        // Rotamos la cola
        enqueue_Nodo(&cola, dequeue_Nodo(&cola));
    }

    // Devuelve el dato encontrado (o NULL si no lo encontró)
    return dato_encontrado;
}

void Escanear(Cola *cola ){
	//vacia
	if(vaciaC(*cola))
	return;

	int *articulos = (int*)peekC(*cola);
	(*articulos)--;

	if(*articulos == 0){

		
		free(dequeue(cola));
	}




}
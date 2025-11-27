#ifndef PILA_H
#define PILA_H

#include "../nodos/nodo.h"

typedef struct
{
	Nodo *cima;
	int capacidad;
	int cantidad;
	void (*imprimir)(void*); //SE ASIGNA LA FUNCION PARA IMPRIMIR LOS DATOS
	void (*liberar)(void*); //SE ASIGNA LA FUNCION PARA LIBERAR DATOS,SI SE NECESITA
}Pila;

typedef struct
{
	char caracter;
	float *valor;
}Dato;



int llena(Pila pila);
int vacia(Pila pila);
void push(Pila *pila,void *dato);
void* pop(Pila *pila);
void imprimirPila(Pila pila);
void imprimirPilaInvertida(Pila pila);
void eliminarPila(Pila *pila);

Pila inicializarPila(int capacidad);

///main
void imprimirEntero(void *dato);
void eliminarSalto(char *arreglo,int tamano);
void imprimirArreglo(char* arr);

int conversion(char* infix, char* postfix, Pila *pila);
int asignarvalor(char caracter);

float evaluarPostfix(Dato *cola, int tam);
int esOperando(char ch);
void asignarValores(Dato* cola, int tamCola);
void generarCola(Dato *cola, char *postfix);
int esBinaria(char* infix);
#endif
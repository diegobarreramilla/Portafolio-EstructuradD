#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;


void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);
void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*));


int calcularAltura(NodoA* raiz);
int Altura(Arbol* arbol);

void borrar(NodoA* raiz);
void borrarArbol(Arbol* arbol);

/*
NodoA* buscar(NodoA* raiz, int dato);
NodoA* buscarDato(Arbol* arbol, int dato);
*/
void eliminar(NodoA** arbol, int dato);
void eliminarNodo(Arbol* arbol,int dato);

int Comparar(Arbol* arbol1, Arbol* arbol2);
int compararDatoArbol(Arbol* arbol1, Arbol* arbol2);
void llenarArregloOrden(NodoA* raiz,int* arreglo, int* indice);
int comparaEstructura(NodoA* raiz1, NodoA* raiz2);
int Estructura(Arbol* arbol1, Arbol* arbol2);

int equilibrar(Arbol* arbol);
int calcularFactorEquilibrio(NodoA* raiz);
void liberaArbol(Arbol* arbol);
void borrarNodos(NodoA* raiz);
NodoA* Reconstruir(void **arreglo, int inicio, int fin);
void llenarArregloReconstruccion(NodoA* raiz,void** arreglo, int* indice);



int* crearEntero(int dato);

int compararEntero(void*a,void*b);




void insertarNodo(Arbol* arbol,void* dato);
void insertarOrdenado(NodoA* raiz, void* dato,int (comparar)(void* dato1,void* dato2));
int vacio(Arbol* arbol);

///recorridos
void preorden(NodoA* raiz);
void Enorden(NodoA* raiz);

void PostOrden(NodoA* raiz);
void enOrdenInverso(NodoA* raiz);

/*
int buscar(Arbol* arbol, void* dato,int comparar(void* dato1, void* dato2));

int buscarDato(NodoA* raiz, void* dato,int comparar(void* dato1, void* dato2));
*/

int calcularAltura(NodoA* raiz);

int Balanceado(Arbol* arbol);

int revisarBalenceo(NodoA* raiz);
int max(int a, int b);

int buscarDato(NodoA* raiz,void* dato, int (comparar)(void* dato1, void* dato2));

int Buscar(Arbol* arbol,void* dato, int(comparar)(void* dato,void* dato1));

int buscaMin(NodoA* raiz);
int min(Arbol*arbol);

int buscaMax(NodoA* raiz);

int maximo(Arbol* arbol);

int cantidadHojas(NodoA* raiz);

int contarHojas(Arbol* arbol);

void imprimirNivel(NodoA* raiz, int nivel);

void recorrerPorNiveles(Arbol* arbol);
#endif
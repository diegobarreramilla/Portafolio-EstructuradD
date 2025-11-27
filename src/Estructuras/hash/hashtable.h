#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> //ELIPSIS
#include "../nodos/nodo.h"
#include "../cola/cola.h"
#include  "../arbol/arbol.h"

extern void* BORRADO;


typedef struct
{
	void **tabla;
	int tam;
	int cant;
	int (*folding)(void*);
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
}HashTable;

int hash(int clave,int tam);
int rehash(int indice,int k,int tam);
HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*));
int insertarClave(HashTable *hashtable,void *dato);
Arbol buscarClave(HashTable* hashtable, void *dato, int (*compararOrden)(void*, void*));
void imprimirHashTabla(HashTable *hashtable);
void insertarRaw(void** tabla, int tam, void* dato, int (*folding)(void*),  int (*comparar)(void*, void*));
void redimensionar(HashTable* hashtable, int nuevoTam);
int eliminarClave(HashTable* hashtable, void *dato);
Arbol imprimirISBM(HashTable* hashtable,int (comparar)(void*,void*));
void buscarClaveAcumulativo(HashTable* hashtable, void *dato, Arbol* arbolAcumulador);
int validarHashTable(HashTable *hashtable);




#endif
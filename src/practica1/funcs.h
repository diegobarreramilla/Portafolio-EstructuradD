#pragma once
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structuras
typedef struct Alumno {
    unsigned int matricula;
    char nombre[64];
    int semestres;
    float promedio;
} Alumno;

typedef struct nodo {
    void *dato;
    struct nodo *sig;
} Nodo;

typedef struct {
    Nodo *inicio;
    int cant;
    int (*comparar)(void*, void*);
    void (*imprimir)(void*);
} Lista;

//Prototipos de lista 
void mostrarLista(Lista);
void insertarOrdenado(Lista*, void*);
void borrarLista(Lista*);
void* buscarDato(Lista, void*);
void borrarDato(Lista*, void*);
void insertarInicio(Lista*, void*);

// Prototipos Alumno 
void* crearAlumno(unsigned int, char*, int, float);
void imprimirAlumno(void*);
int compararPorMatricula(void*, void*);
int compararPorNombre(void*, void*);
int compararPorSemestres(void*, void*);
int compararPorPromedio(void* , void*);



#pragma once
#include <stdio.h>
#include <stdlib.h>

// Direcciones posibles 
#define ARRIBA 1
#define ABAJO 2
#define DERECHA 4
#define IZQUIERDA 8

///tamano
#define REN 27
#define COL 26

//  coordenadas
typedef struct {
    int x, y;
} Coordenada;

// Nodo para la pila
typedef struct Nodo {
    Coordenada *coord;
    struct Nodo *sig;
} Nodo;

// Pila
typedef struct {
    Nodo *cima;
} Pila;


unsigned char **crear_laberinto(void);
void imprimirLab(unsigned char **lab);

Coordenada* crearCoordenada(int x,int y);
int compararCoordenada(void *a,void *b);
void imprimirCoordenada(void *dato);

unsigned char alternativas(unsigned char **lab,Coordenada *coordenada);
void imprimirPosibles(unsigned char caminos);

// Funciones de pila
Pila* crearPila();
void push(Pila *pila, Coordenada *coord);
Coordenada* pop(Pila *pila);
Coordenada* peek(Pila *pila);
int pilaVacia(Pila *pila);

void resolver(unsigned char **lab);

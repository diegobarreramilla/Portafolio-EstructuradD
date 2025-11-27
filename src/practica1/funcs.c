
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "funcs.h"


Nodo* crearNodo(void* dato) {
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    return nuevo;
}


void mostrarLista(Lista lista) {
    Nodo *p = lista.inicio;
    printf("\nLista (%d): ", lista.cant);
    while(p) {
        lista.imprimir(p->dato);
        printf(" -> ");
        p = p->sig;
    }
    printf("NULL\n");
}



void insertarOrdenado(Lista *lista, void* dato) {
    Nodo *nuevo = crearNodo(dato);
    Nodo *actual = lista->inicio, *anterior = NULL;

    while(actual && lista->comparar(dato, actual->dato) > 0) {
        anterior = actual;
        actual = actual->sig;
    }

    if(anterior == NULL) { 
        nuevo->sig = lista->inicio;
        lista->inicio = nuevo;
    } else {
        anterior->sig = nuevo;
        nuevo->sig = actual;
    }
    lista->cant++;
}

void borrarLista(Lista *lista) {
    Nodo *actual = lista->inicio, *tmp;
    while(actual) {
        tmp = actual;
        actual = actual->sig;
        free(tmp->dato);
        free(tmp);
    }
    lista->inicio = NULL;
    lista->cant = 0;
}

void* buscarDato(Lista lista, void *dato) {
    Nodo *actual = lista.inicio;
    while(actual) {
        if(lista.comparar(dato, actual->dato) == 0)
            return actual->dato;
        actual = actual->sig;
    }
    return NULL;
}

void borrarDato(Lista *lista, void *dato) {
    Nodo *actual = lista->inicio, *anterior = NULL;
    while(actual) {
        if(lista->comparar(dato, actual->dato) == 0) {
            if(anterior) anterior->sig = actual->sig;
            else lista->inicio = actual->sig;
            free(actual->dato);
            free(actual);
            lista->cant--;
            return;
        }
        anterior = actual;
        actual = actual->sig;
    }
}

//crar alumno
void* crearAlumno(unsigned int matricula, char *nombre, int semestres, float promedio) {
    Alumno *nuevo = malloc(sizeof(Alumno));
    nuevo->matricula = matricula;
    strcpy(nuevo->nombre, nombre);
    nuevo->semestres = semestres;
    nuevo->promedio = promedio;
    return nuevo;
}

void imprimirAlumno(void* a) {
    Alumno *al = (Alumno*)a;
    printf("[%u | %s | %d sem | %.2f]", al->matricula, al->nombre, al->semestres, al->promedio);
}

int compararPorMatricula(void* a, void* b) {
    return ((Alumno*)a)->matricula - ((Alumno*)b)->matricula;
}
int compararPorNombre(void* a, void* b) {
    return strcmp(((Alumno*)a)->nombre, ((Alumno*)b)->nombre);
}
int compararPorSemestres(void* a, void* b) {
    return ((Alumno*)a)->semestres - ((Alumno*)b)->semestres;
}
int compararPorPromedio(void* a, void* b) {
    float x = ((Alumno*)a)->promedio, y = ((Alumno*)b)->promedio;
    if(x < y) return -1;

    if(x > y) return 1;
    return 0;
}

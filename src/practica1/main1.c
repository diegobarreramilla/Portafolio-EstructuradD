#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "funcs.h"


int main() {
    Lista lista = {NULL, 0, compararPorMatricula, imprimirAlumno};
    int opcion;
    do {
        printf("\nMENU \n");
        printf("1-registrar alumno\n");
        printf("2-desplegar alumnos\n");
        printf("3-reordenar lista\n");
        printf("4-buscar alumno\n");
        printf("5-borrar alumno\n");
        printf("6-salir\n");
        printf("opcion:");
        scanf("%d", &opcion);

        if(opcion == 1) {
            unsigned int mat;
            char nombre[64];
            int sem;
            float prom;
            printf("Matricula: "); 
            scanf("%u", &mat);
            printf("Nombre: "); 
            scanf("%s", nombre);
            printf("Semestres: "); 
            scanf("%i", &sem);
            printf("Promedio: "); 
            scanf("%f", &prom);
            insertarOrdenado(&lista, crearAlumno(mat, nombre, sem, prom));
        }
        else if(opcion == 2) {
            mostrarLista(lista);
        }
        else if(opcion == 3) {
            printf("Ordenar por: 1=matricula, 2=nombre, 3=semestres, 4=promedio: ");
            int opc; 
            scanf("%d", &opc);

            Lista aux = {NULL, 0, NULL, imprimirAlumno};
            if(opc==1) aux.comparar = compararPorMatricula;
            else if(opc==2) aux.comparar = compararPorNombre;
            else if(opc==3) aux.comparar = compararPorSemestres;
            else aux.comparar = compararPorPromedio;

            Nodo *p = lista.inicio;
            while(p) {
                Alumno *al = (Alumno*)p->dato;
                insertarOrdenado(&aux, crearAlumno(al->matricula, al->nombre, al->semestres, al->promedio));
                p = p->sig;
            }
            borrarLista(&lista);
            lista = aux;
        }
        else if(opcion == 4) {
            printf("Buscar por: 1=matricula, 2=nombre, 3=semestres, 4=promedio: ");
    int crit; 
    scanf("%d", &crit);

    Alumno* tmp = malloc(sizeof(Alumno)); 
    tmp->matricula = 0;
    strcpy(tmp->nombre, ""); 
    tmp->semestres = 0;
    tmp->promedio = 0.0f;

    if(crit == 1) { 
        printf("Matricula: ");
        scanf("%u", &tmp->matricula);
        lista.comparar = compararPorMatricula;
    }
    else if(crit == 2) { 
        printf("Nombre: "); 
        char nombre[64];
        scanf("%63s", nombre);          
        strcpy(tmp->nombre, nombre);   
        lista.comparar = compararPorNombre;
    }
    else if(crit == 3) { 
        printf("Semestres: "); 
        scanf("%d", &tmp->semestres);
        lista.comparar = compararPorSemestres;
    }
    else { 
        printf("Promedio: "); 
        scanf("%f", &tmp->promedio);
        lista.comparar = compararPorPromedio;
    }

    Alumno* res = buscarDato(lista, tmp);
    if(res) imprimirAlumno(res);
    else printf("No encontrado\n");

    free(tmp); 
        }
        else if(opcion == 5) {
            unsigned int mat;
            printf("Matricula a borrar: ");
            scanf("%u", &mat);
            Alumno tmp = {mat,"",0,0.0};
            borrarDato(&lista, &tmp);
        }
    } while(opcion != 6);

    borrarLista(&lista);
    return 0;
}

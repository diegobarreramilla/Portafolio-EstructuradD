#ifndef CAPTURA_H
#define CAPTURA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void clear_buffer(void);
void remover_salto(char *cadena);
int inputEntero(char *mensaje,int *valor);
int inputFloat(char *mensaje,float *valor);
int inputDouble(char *mensaje,double *valor);
int inputChar(char *mensaje,char *valor);
int inputCadena(char *mensaje,char *cadena,int longitud);
int inputCadenaDinamica(char *mensaje,char **cadena,int max);
char* cadenaDinamica(const char * cadena);
void eliminarSalto(char *arreglo, int tamano);


#endif
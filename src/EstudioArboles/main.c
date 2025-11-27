#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

int main(void){
    Arbol arbol;
    arbol.comparar = &compararEntero;
    arbol.cantidad =0;
    arbol.raiz = NULL;
    arbol.imprimir = &imprimirEntero;
    int a=4,b=5,c=7,d=9,e=1;

    insertarNodo(&arbol,&a);
    
    insertarNodo(&arbol,&c);
    
    insertarNodo(&arbol,&b);
    
    insertarNodo(&arbol,&d);
    imprimirArbol(arbol);
	printf("\nPreorden: \n\n");
	preorden(arbol.raiz);
	printf("\nPostorden: \n\n");
	PostOrden(arbol.raiz);
	printf("\nPInverso \n\n");
	enOrdenInverso(arbol.raiz);
	/*
	int resultado = buscar(&arbol,&e,arbol.comparar);
	if(resultado == 1){
		printf("\nSe encontro\n");

	}else if (resultado == 0){
		printf("\nNo se encotro\n");
	}else{
		printf("\nArbol vacio\n");
	}*/
	printf("\n\n");
	int altura = Altura(&arbol);
	printf("\nAltura:%i",altura);

	int balance = Balanceado(&arbol);
	if(balance >=1){
	printf("\nEL ARBOL ESTA BALANCEADO\n");
	}else{
		printf("\nARBOL NO BALANCEADO");
	}

	int busqueda = Buscar(&arbol,&e,arbol.comparar);

	if(busqueda){
		printf("\n\nENCONTRADO\n\n");
	}else{
		printf("\n\nNO ENCONTRADO\n\n");
	}

	int hojas = contarHojas(&arbol);
	printf("\n\nCANTIDAD DE HOJAS: %i\n\n",hojas);

	recorrerPorNiveles(&arbol);



    return 0;
}
/*
int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}


void myprintf(char *formato,...)
{
	va_list args;
    va_start(args, strlen(formato));
	while(*formato!='\0')
	{
		switch(*formato)
		{
			case 'd':
				printf("%d",(int)va_arg(args, int));
				break;
			case 'c':
				printf("%c",(char)va_arg(args, char));				
				break;
		}
		formato++;
	}
	va_end(args);
}
*/
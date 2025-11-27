#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/cola/cola.h"


#define NUMERO_CAJAS 5
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_ARTICULOS 1
#define MAX_ARTICULOS 5

typedef struct
{
	Cola cola;
	int estado ;
}Caja;


int* generar_articulos(void);
void imprimirEntero(void*);

int main(void)
{
	Caja cajas[NUMERO_CAJAS];
	
	for(int i=0; i<NUMERO_CAJAS ; i++)
	{
		cajas[i].cola = inicializarCola(20);

		cajas[i].estado = 1;
		cajas[i].cola.imprimir = &imprimirEntero;
	}


	int opcion;	
	do
	{
		
		for(int i=0; i<NUMERO_CAJAS ; i++)
		{
			if(cajas[i].estado ==1 )
			printf("\n* Caja[%d]: ",i+1);
			else
			printf("\nX Caja[%d]: ",i+1);

			imprimirCola(cajas[i].cola);
		}
		opcion = 0;
		//DESPLEGAR LAS CAJAS
		printf("\n [1] GENERAR CLIENTE");
		printf("\n [2] ESCANEAR ARTUCLOS");
		printf("\n [3] HABILITAR CAJA");
		printf("\n [4] CERRAR CAJA");
		printf("\n [5] TERMINAR");
		inputEntero("\n Selecciona opcion: ",&opcion);
		switch(opcion)
		{
			case 1:
			for(int i=0; i<NUMERO_CAJAS ; i++)
			{
				//SI ESTA HABILITADA Y SI NO ESTA LLENA
				//GENERAR Y FORMAR CLIENTE
				if(cajas[i].estado  == 1&& !llenaC(cajas[i].cola))
					enqueue( &cajas[i].cola , generar_articulos() );
			}
			break;



			case 2:
				
			for(int i =0; i<NUMERO_CAJAS;i++){

				 
					Escanear(&cajas[i].cola );

				 

			}


			break;

			case 3:
			
			printf("\nIntroducir el numero de la caja que habilitara: \n");
			int cambio;
			scanf("%i",&cambio);
			cambio--;

			if(cajas[cambio].estado == 0){

				cajas[cambio].estado =1;
			}else{

				printf("La caja ya esta abierta\n");
			}
			


			break;


			case 4:
			printf("\nIntroducir el numero de la caja que cambiara de cerrar: \n");
			int cambio1;
			scanf("%i",&cambio1);
			cambio1--;

			if(cajas[cambio1].estado == 1){

				cajas[cambio1].estado =0;
			}else{

				printf("La caja ya esta cerrada\n");
			}
			
			

			break;


			default:
			printf("\n [DEFAULT]");
				
		}	
	}while(opcion!=5);
	
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}


int* generar_articulos(void)
{		
	int *articulos = malloc(sizeof(int));
	*articulos = rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
	return articulos; 
	
}


void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}
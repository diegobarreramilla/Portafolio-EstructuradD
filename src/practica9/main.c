#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/heap/heap.h"



int compararEntero(void*,void*);
void imprimirEntero(void*);
int main(void)
{
	Heap heap = inicializarHeap( &imprimirArchivo,&compararArchivo);
	int cantidadInicio=6;
	char *nombres[] = {"Calendario","Practica7","Factura","Recibo","VScode.exe","Recibo2"};
	int tamano[] ={12,2,45,39,45,4};
	int opc;

	char nombre[50];
	int paginas;
	int indice;

	for(int i =0;i<cantidadInicio;i++){
	void* nuevo = crearArchivo(nombres[i],tamano[i]);
	insertarHeap(&heap,nuevo);
	}



	

	do{
		///imrpimir los primeros 5 archivos
		for(int i =0;i<5 && i< heap.cantidad;i++){
			if(heap.arr[i]->dato != NULL && heap.arr[i]){
			imprimirArchivo(heap.arr[i]->dato);
			}else{
				printf("-----------");
			}
		}
		if(heap.tipo ==1)
			printf("Prioridad del heap : MAX\n");
		if(heap.tipo ==0)
			printf("Prioridad del heap : MIN\n");
		
		printf("[0] Cambiar Prioridad\n");
		printf("[1] Mostrar Cola impresion\n");
		printf("[2] Agregar Archivo\n");
		printf("[3] Procesar archivo prioritario\n");
		printf("[4] Eliminar archivo\n");
		printf("[5] Elimiar todos los archvos\n");
		printf("[6] Salir\n");
		scanf("%i",&opc);

		switch (opc)
		{
		case 0:
			if(heap.tipo == MAX ){
				heap.tipo = MIN;

			}else{
				heap.tipo = MAX;
			}

			heapify(&heap);

			printf("\nPrioridad cambiada\n");
			
			break;
		case 1:
		printf("Cola de impresion completa\n");
		imprimirHeap(heap);
		printf("\n\n\n");

		printf("\nArbol de representacion:\n");
		imprimirArbol(heap.arbol);
		printf("\n");
		
			break;
		case 2:

		printf("\nIntroduzca el nombre del archivo a agregar: \n");
		scanf("%s",nombre);
		printf("Introduzca la cantidad de paginas que tiene: ");
		scanf("%i",&paginas);

		insertarHeap(&heap,crearArchivo(nombre,paginas));
		printf("\n\n");
			break;
		case 3:
		printf("\nRaiz procesada: \n");
		imprimirArchivo(procesarraiz(&heap));
		printf("\n\n");
			
			break;
		case 4:
		printf("\nIntroduzca el indice del archivo a eliminar\n");
		scanf("%i",&indice);

		eliminarNodoEspecifico(&heap,indice);
			
		
			break;

			case 5:
		vaciarHeap(&heap);
		
			break;
		case 6:
		
			
			break;
		
		default:
			break;
		}
		

	}while(opc != 6);
	
	return 0;
}


void imprimirEntero(void *a)
{
	int *aa=a;
	printf(" %d",*aa);
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}
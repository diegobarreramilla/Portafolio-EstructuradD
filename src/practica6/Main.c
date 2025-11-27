#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);

void myprintf(char *formato,...);

int main(void)
{
    
    int altura;
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;


    
    Arbol arbol1;
    arbol1.raiz = NULL;
    arbol1.cantidad =0;
    arbol1.comparar = &compararEntero;
    arbol1.imprimir = &imprimirEntero;

    ///Menu de opciones
    int opc;
    int num;
    int datosiguales;
    int mismaestructura;
    //int factorequilibrio;
    int eq1;
    int eq2;
    do{
        
        printf("\n1-Anadir dato a Arbo 1");
        printf("\n2-Anadir dato a Arbol 2");
        printf("\n3-Comparar arboles");
        printf("\n4-Eliminar dato Arbol 1");
        printf("\n5-Eliminar dato Arbol 2");
        printf("\n6-Desplegar altura Arboles");
        printf("\n7-Equilibar arboles");
        printf("\n8-Mostrar Arboles");
        printf("\n9-Terminar programa"); 
        printf("\nSeleccionar opcion: \n"); 
        scanf("%i",&opc);
        

        switch (opc){

        case 1:
            printf("\nIntroducir el dato entero a anadir al arbol 1:\n");
            scanf("%i",&num);
            printf("\nARBOL 1:\n\n");
            insertarArbol(&arbol, crearEntero(num));
            imprimirArbol(arbol);
            printf("\n\n");
            break;


        case 2:
            printf("\nIntroducir el dato entero a anadir a arbol 2:\n");
            scanf("%i",&num);
            insertarArbol(&arbol1, crearEntero(num));
            printf("\nARBOL 2:\n\n");
            imprimirArbol(arbol1);
            printf("\n\n");
            break;

            
        case 3:
            
            datosiguales = Comparar(&arbol,&arbol1);
            if(datosiguales == 0){
                printf("\nLos arboles contienen datos diferentes o alguno es NULL\n");
            }
            else if(datosiguales == 1){
                printf("\nLos arboles continen los mismos datos\n");
                mismaestructura = Estructura(&arbol,&arbol1);
                if(mismaestructura == 1){
                    printf("Y comparten la misma estructura\n");
                }
                else{
                    printf("Pero no comparten la misma estructura\n");
                }


            }
            break;
        case 4:
            printf("\nIntroducir el dato a elimiar del arbol 1:\n");
            scanf("%i",&num);    
            eliminarNodo(&arbol,num);
            imprimirArbol(arbol);
            break;

        case 5:
            printf("\nIntroducir el dato a elimiar del arbol 2:\n");
            scanf("%i",&num);    
            eliminarNodo(&arbol1,num);
            imprimirArbol(arbol1);
            break;
            
        case 6:

            altura = Altura(&arbol);
            printf("\nLa altura del arbol 1 es de: %i\n",altura);
            altura = Altura(&arbol1);
            printf("\nLa altura del arbor 2 es de: %i\n",altura);

            imprimirArbol(arbol);
            printf("\n\n");
            imprimirArbol(arbol1);
            break;
                
        case 7:
            eq1 = equilibrar(&arbol);
            eq2 =equilibrar(&arbol1);

            if(eq1 == 1){
            printf("\n\nArbol equilibrado 1:\n\n");
            imprimirArbol(arbol);
            }else{
                printf("\nEl Arbol 1 no debia ser equilibrado\n");
            }

            if(eq2 == 1){
            printf("\n\nArbol equilibrado 2:\n\n");
            imprimirArbol(arbol);
            }else{
                printf("\nEl Arbol 2 no debia ser equilibrado\n");
            }


            break;

        case 8:
            printf("\nARBOL 1:\n\n");
            imprimirArbol(arbol);
            printf("\nARBOL 2:\n\n");
            imprimirArbol(arbol1);
            break;
            
        case 9:
        printf("SALIENDO");
            

        break;

        default:
        printf("\n[DEFALUT]\n");

            


        }
        



    }while(opc!=9);
    
    /*
    ///nodos
	insertarArbol(&arbol, crearEntero(4));
	insertarArbol(&arbol, crearEntero(2));
    insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(6));
	insertarArbol(&arbol, crearEntero(3));
	insertarArbol(&arbol, crearEntero(7));
    insertarArbol(&arbol, crearEntero(8));
	insertarArbol(&arbol, crearEntero(5));
	imprimirArbol(arbol);
	///desplegar cada tipo de orden
	printf("\n PREORDEN: ");
	imprimirOrden(arbol,PREORDEN);
	printf("\n ORDEN: ");
	imprimirOrden(arbol,ORDEN);
	printf("\n INVERSO: ");
	imprimirOrden(arbol,INVERSO);
	printf("\n POSTORDEN: ");
	imprimirOrden(arbol,POSTORDEN);


    ////calcular altura
    altura = Altura(&arbol);
    printf("\nAltura: %i",altura);

    ///eliminar nodo
    eliminarNodo(&arbol,1); 
    printf("\n\n\nprueba elimar 1");
    imprimirArbol(arbol);


    ///borar arbol
     borrarArbol(&arbol);
     if(arbol.raiz == NULL){
        printf("\nArbol Vacio");
     }else{
            imprimirArbol(arbol);
     }*/

    
	
	printf("\n\nFIN DE PROGRAMA\n");
	return 0;
}


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

/*
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
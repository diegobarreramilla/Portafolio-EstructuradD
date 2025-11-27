#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include<ctype.h>
#include "../captura/captura.h" 
#include "../Estructuras/pila/pila.h"
#include "../Estructuras/cola/cola.h"
#include "../Estructuras/arbol/arbol.h" 
#include "../Estructuras/nodos/nodoarbol.h"




Dato* crearDato(char c);


int compararDatoChar(void *dato1, void *dato2);
NodoA* crearArbolDeExpresion(char *postfix, Pila *pila_arbol, Cola *cola_datos);
void capturarValoresOperandos(Cola *cola_datos);
float evaluarArbol(NodoA *nodo);
void imprimirArbolInorden(NodoA *nodo);
void liberarArbol(NodoA *nodo);
void imprimirDato(void *dato);
void imprimirArbolVisual(NodoA *raiz);
void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*));


NodoA *raiz = NULL;
char *postfix = NULL;


int main(void)
{
    
    Cola cola_datos = inicializarCola(100); 
  
    Pila pila = inicializarPila(100);
    int opc = 0;

    do {
       
        printf("[1] Ingresar cadena infix\n");
        printf("[2] Imprimir arbol de expresion\n");
        printf("[3] Evaluar expresion\n");
        printf("[4] Salir\n");
        printf("Opcion: ");
        scanf("%d", &opc);
        while(getchar() != '\n'); 

        switch(opc)
        {
            case 1: 
            {
                char arreglo[100];
                 printf("Introduce la exprecion infix ");
                fgets(arreglo, sizeof(arreglo), stdin);
                int tamano = strlen(arreglo);
                eliminarSalto(arreglo, tamano); 

                char *arr = malloc((tamano+1) * sizeof(char));
                strcpy(arr, arreglo);

                
                if(postfix) free(postfix);
                if(raiz) liberarArbol(raiz);
                while(!vaciaC(cola_datos)) { 
                    Dato *d = (Dato*)dequeue(&cola_datos);
                    if(d->valor) free(d->valor);
                    free(d);
                }
                raiz = NULL;
                
                postfix = malloc((tamano+2) * sizeof(char)); 

                
                if(conversion(arr, postfix, &pila) == 1){
                    printf("\nPostfix: %s\n", postfix);
                    
                    
                    raiz = crearArbolDeExpresion(postfix, &pila, &cola_datos);
                    printf("Arbol de expresion creado\n");

                } else {
                    printf("\nNo valida.\n");
                    if(postfix) {
                        free(postfix);
                        postfix = NULL;
                    }
                }
                free(arr);
            }
            break;

            case 2: 
                if(!raiz) {
                    printf("Arbol vacio\n");
                } else {
                    printf("\nArbol: \n");
                    imprimirArbolVisual(raiz);
                    printf("\n");
                }
                break;

            case 3: 
                if(!raiz) {
                    printf("No hay expresiona evaluar\n");
                    break;
                }
                
                
                printf("Captura de Valores \n");
                capturarValoresOperandos(&cola_datos);

                // 2. Evaluar arbol
                float resultado = evaluarArbol(raiz);
                printf("\nEl resultado es: %.2f\n", resultado);
                break;

            case 4: 
                printf("Fin\n");
                if(postfix) free(postfix);
                if(raiz) liberarArbol(raiz);
                
                
                while(!vaciaC(cola_datos)) {
                    Dato *d = (Dato*)dequeue(&cola_datos);
                    if(d->valor) free(d->valor);
                    free(d);
                }
                eliminarPila(&pila);
                break;

            default:
                printf("Error\n");
                break;
        }

    } while(opc != 4);

    return 0;
}




Dato* crearDato(char c)
{
    Dato *d = (Dato*)malloc(sizeof(Dato));
    d->caracter = c;
    d->valor = NULL; 
    return d;
}

int compararDatoChar(void *dato1, void *dato2) {
    Dato *d = (Dato*)dato1;
    char *c = (char*)dato2;
    
    return (d->caracter == *c) ? 0 : 1; 
}

void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
    {
        printf(" ");
        imprimir(nodo->dato); 
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      "); 
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i == nivel)
                    printf(" |      ");
                else
                    printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      "); 
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirDato(void *dato)
{
    if (!dato) return;
    Dato *d = (Dato*)dato;
    printf("%c", d->caracter); 
}

void imprimirArbolVisual(NodoA *raiz)
{
    if (!raiz) {
        printf("Arbol vacio.\n");
        return;
    }
    
    imprimir_arbol(raiz, 0, imprimirDato);
    printf("\n");
}

NodoA* crearArbolDeExpresion(char *postfix, Pila *pila_arbol, Cola *cola_datos)
{
   
    eliminarPila(pila_arbol); 

    for(int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];
        Dato *dato_nodo = NULL;

        if(esOperando(c))
        {
           
            dato_nodo = (Dato*)buscarC(*cola_datos, &c, compararDatoChar);

            if(dato_nodo == NULL) {
                
                dato_nodo = crearDato(c);
                enqueue(cola_datos, dato_nodo); 
            }
            
            
            NodoA *nodo_hoja = crearNodoA(dato_nodo);
            push(pila_arbol, nodo_hoja);

        } 
        else
        {
            
            dato_nodo = crearDato(c);
            NodoA *nodo_op = crearNodoA(dato_nodo);

            
            nodo_op->dch = (NodoA*)pop(pila_arbol);
            nodo_op->izq = (NodoA*)pop(pila_arbol);

            
            push(pila_arbol, nodo_op);
        }
    }

    
    return (NodoA*)pop(pila_arbol);
}


void capturarValoresOperandos(Cola *cola_datos)
{
    int n = cola_datos->cantidad;
    for (int i = 0; i < n; i++)
    {
        Dato *d = (Dato*)peekC(*cola_datos);
        
        
        if (d->valor == NULL) {
            d->valor = (float*)malloc(sizeof(float));
            printf("Ingrese el valor para %c: ", d->caracter);
            scanf("%f", d->valor);
            while(getchar() != '\n');
        }

       
        enqueue(cola_datos, dequeue(cola_datos));
    }
}


float evaluarArbol(NodoA *nodo)
{
    if (nodo == NULL)
     return 0;

    Dato *d = (Dato*)nodo->dato;

    
    if (esOperando(d->caracter)) {
        if(d->valor != NULL) {
            return *(d->valor);
        } else {
            printf("Error: Valor de %c no capturado.\n", d->caracter);
            return 0;
        }
    }

    
    float val_izq = evaluarArbol(nodo->izq);
    float val_dch = evaluarArbol(nodo->dch);

    switch(d->caracter) {
        case '+': return val_izq + val_dch;
        case '-': return val_izq - val_dch;
        case '*': return val_izq * val_dch;
        case '/': return val_izq / val_dch; 
        case '^': return pow(val_izq, val_dch);
        default:
            printf("Operador desconocido: %c\n", d->caracter);
            return 0;
    }
}


void imprimirArbolInorden(NodoA *nodo)
{
    if (nodo == NULL) return;

    Dato *d = (Dato*)nodo->dato;

    if (esOperando(d->caracter)) {
        printf("%c", d->caracter);
    } else {
        
        printf("(");
        imprimirArbolInorden(nodo->izq);
        printf(" %c ", d->caracter);
        imprimirArbolInorden(nodo->dch);
        printf(")");
    }
}


void liberarArbol(NodoA *nodo)
{
    if (nodo == NULL) return;

    
    liberarArbol(nodo->izq);
    liberarArbol(nodo->dch);

    Dato *d = (Dato*)nodo->dato;
    
    
    if (!esOperando(d->caracter)) {
        free(d); 
    }
    
    free(nodo); 
}
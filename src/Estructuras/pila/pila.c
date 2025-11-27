#include "pila.h"
#include <stdio.h>
#include <stdint.h> 
#include <string.h>
#include<ctype.h>


int llena(Pila pila)
{
	return pila.cantidad == pila.capacidad;
}
int vacia(Pila pila)
{
	return pila.cantidad == 0 && pila.cima==NULL ;
}
void push(Pila *pila,void *dato)
{
	if(llena(*pila))
	{
		printf("\n Overflow");
	}
	else
	{
		Nodo *nuevo = crearNodo(dato);
		nuevo->sig = pila->cima;
		pila->cima = nuevo;
		pila->cantidad++;
	}
}
void* pop(Pila *pila)
{
	if(vacia(*pila))
	{
		printf("\n Underflow");
		return NULL;
	}
	else
	{
		//DESENCADENAR EL NODO
		Nodo *aux = pila->cima;		
		pila->cima = aux->sig;
		aux->sig = NULL;
		//EXTRAER EL DATO
		void *dato = aux->dato;
		//LIBERAR EL NODO
		free(aux);
		pila->cantidad--;
		return dato;
	}
}
void* peek(Pila pila)
{
    if (vacia(pila))
    {
        return NULL; 
    }
    else
    {
        
        return pila.cima->dato;
    }
}

void push_nodo(Pila *pila,Nodo *nuevo)
{
	if(llena(*pila))
	{
		printf("\n Overflow");
	}
	else
	{
		nuevo->sig = pila->cima;
		pila->cima = nuevo;
		pila->cantidad++;
	}
}

Nodo* pop_nodo(Pila *pila)
{
	if(vacia(*pila))
	{
		printf("\n Underflow");
		return NULL;
	}
	else
	{
		//DESENCADENAR EL NODO
		Nodo *aux = pila->cima;		
		pila->cima = aux->sig;
		aux->sig = NULL;
		pila->cantidad--;
		return aux;
	}
}

void imprimirPila(Pila pila)
{
	Pila aux = (Pila){NULL,pila.capacidad,0,NULL};
	Nodo *nodo;
	printf("\n\nPila [%d]:",pila.cantidad);
	while( !vacia(pila) )
	{
		nodo = pop_nodo(&pila);
		printf("\n ");
		pila.imprimir(nodo->dato);
		push_nodo(&aux,nodo);
	}
	while( !vacia(aux) )
		push_nodo(&pila,pop_nodo(&aux));
}
void imprimirPilaInvertida(Pila pila)
{
	Pila aux = (Pila){NULL,pila.capacidad,0,NULL};
	Nodo *nodo;
	printf("\n\nPila Invertida [%d]:",pila.cantidad);
	while( !vacia(pila) )
		push_nodo(&aux,pop_nodo(&pila));
	while( !vacia(aux) )
	{		
		nodo = pop_nodo(&aux);
		printf("\n ");
		pila.imprimir(nodo->dato);
		push_nodo(&pila,nodo);
	}	
}

void eliminarPila(Pila *pila)
{
	void *dato;
	while(!vacia(*pila))
	{
		dato = pop(pila);
		if( pila->liberar )
			pila->liberar(dato);
	}
}



//////////
Pila inicializarPila(int capacidad) {
    Pila p;
    p.cima = NULL;
    p.capacidad = capacidad;  
    p.cantidad = 0;
    p.imprimir = NULL; 
    p.liberar = NULL;  
    return p;
}


void verificarPalindromo() {
    char str[100];
    printf("Ingresa la cadena: ");
    fgets(str, sizeof(str), stdin);

    Pila pila = inicializarPila(100);

    // meter  datos de arreglo a pila
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\n') {
            char *c = malloc(sizeof(char));
            *c = str[i];
            push(&pila, c);
        }
    }

	///comparar arreglo inicial con pop
    int esPalindromo = 1;
    for (int i = 0; str[i]; i++) {
		//no permitir espacio ni salto
        if (str[i] != ' ' && str[i] != '\n') {
			///pop
            char *c = (char*)pop(&pila);
			///si no es o vacia
            if (!c || *c != str[i]) {
                esPalindromo = 0;
                if (c) free(c);
                break;
            }
            free(c);
        }
    }

    if (esPalindromo == 1){
	printf("Es palindromo\n");
	}
    else {
	printf("NO es  palindromo\n");
	}

    eliminarPila(&pila);
}


void verificarParentesis() {
    char str[100];
	///guardamis cadena
    printf("Ingresa la cadena: ");
    fgets(str, sizeof(str), stdin);

    Pila pila = inicializarPila(100);
    int valido = 1;

	///recorremos
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
		////metemos si es abridor
        if (c == '(' || c == '{' || c == '[') {
            char *aux = malloc(sizeof(char));
            *aux = c;
            push(&pila, aux);
        } else if (c == ')' || c == '}' || c == ']') {

            if (vacia(pila)) { 
				valido = 0; break; 
			}
			///guardamos el cierre
            char *cima = (char*)pop(&pila);
			///comparamos el actual con el pop
            if (!cima || (c == ')' && *cima != '(') || (c == '}' && *cima != '{') ||  (c == ']' && *cima != '[')) {
                valido = 0;
                if (cima) free(cima);
                break;
            }
            free(cima);
        }
    }

    if (!vacia(pila)) valido = 0;

    if (valido) printf("Cadena valida\n");
    else printf("Cadena no valida \n");

    eliminarPila(&pila);
}




void imprimirArreglo(char* arr){
	for(int i =0; arr[i]!= '\0';i++){
	printf("%c",arr[i]);

	}
}


int esOperando(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}


int asignarvalor(char caracter) {
    switch (caracter) {
        case '-': case '+': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
    }
    return -1;
}


/*
int conversion(char* infix, char* postfix, Pila *pila) {
    int i, k = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char act = infix[i];

        if (esOperando(act)) {
            postfix[k++] = act;
        }
        else if (act == '(') {
            char *c = malloc(sizeof(char));
            *c = act;
            push(pila, c);
        }
        else if (act == ')') {
            while (!vacia(*pila) && *(char*)peek(*pila) != '(') {
                char *op = (char*)pop(pila);
                postfix[k++] = *op;
                free(op);
            }

 
            if (vacia(*pila)) {
                printf("\nParentesis de cierre ')' sin su apertura '('.\n");
                eliminarPila(pila); 
                return 0; 
            }
            
            
            free(pop(pila));
        }
        else { 
            while (!vacia(*pila) && asignarvalor(act) <= asignarvalor(*(char*)peek(*pila))) {
                char *op = (char*)pop(pila);
                postfix[k++] = *op;
                free(op);
            }
            char *c = malloc(sizeof(char));
            *c = act;
            push(pila, c);
        }
    }

   
    while (!vacia(*pila)) {
        char *op_ptr = (char*)peek(*pila);

      
        if (*op_ptr == '(') {
            printf("\nParentesis de apertura '(' sin su  cierre ')'.\n");
            eliminarPila(pila); 
            return 0; 
        }
        
        op_ptr = (char*)pop(pila);
        postfix[k++] = *op_ptr;
        free(op_ptr);
    }

    postfix[k] = '\0';
    return 1; 
}
*/

int esBinaria(char* infix) {
    int estado = 0; // 0 espera operando 1 espera opeador
    char anterior = '\0'; 

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        
        if (isspace(c) || c == '(' || c == ')') {
            continue;
        }

        if (esOperando(c)) {
            if (estado == 0) { 
                estado = 1; 
                anterior = c;
            } else {
                // Error se esperaba un operador
                printf("\nEROR de expresion\n", c);
                return 0;
            }
        } else { // Es un operador
            if (estado == 1) { // Si esperabamos operador
                estado = 0; // Ahora esperamos operando
                anterior = c;
            } else {
                // Error se esperaba un operando
                printf("\nERROR\n", c);
                return 0;
            }
        }
    }
    
    // Validar que no estvaci
    if (anterior == '\0') {
        printf("\nERROR\n");
        return 0;
    }

    
    if (estado == 0) { 
         printf("\nERROR termina en operador\n");
         return 0;
    }

    return 1; 
}

// Conversonde infix a postfix
int conversion(char* infix, char* postfix, Pila *pila) {

    if (esBinaria(infix) == 0) {
        
        return 0; 
    }
    int i, k = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char act = infix[i];

        if (esOperando(act)) {
            postfix[k++] = act;
        }
        else if (act == '(') {
            char *c = malloc(sizeof(char));
            *c = act;
            push(pila, c);
        }
        else if (act == ')') {
            while (!vacia(*pila) && *(char*)peek(*pila) != '(') {
                char *op = (char*)pop(pila);
                postfix[k++] = *op;
                free(op);
            }
            if (vacia(*pila)) {
                printf("\nParentesis de cierre ')' sin apertura '('.\n");
                eliminarPila(pila);
                return 0;
            }
            free(pop(pila));
        }
        else { // operadores
            while (!vacia(*pila) && asignarvalor(act) <= asignarvalor(*(char*)peek(*pila))) {
                char *op = (char*)pop(pila);
                postfix[k++] = *op;
                free(op);
            }
            char *c = malloc(sizeof(char));
            *c = act;
            push(pila, c);
        }
    }

    while (!vacia(*pila)) {
        char *op_ptr = (char*)peek(*pila);
        if (*op_ptr == '(') {
            printf("\nParentesis de apertura '(' sin cierre ')'.\n");
            eliminarPila(pila);
            return 0;
        }
        op_ptr = (char*)pop(pila);
        postfix[k++] = *op_ptr;
        free(op_ptr);
    }

    postfix[k] = '\0';
    return 1;
}

// Pide al usuario los valores de los operandos y los asigna a la estructura Dato
void asignarValores(Dato* cola, int tamCola) {
    for (int i = 0; i < tamCola; i++) {
        if (cola[i].valor == NULL) { // Si es operador, saltamos
            continue;
        }

        // Es operando, pedimos valor
        printf("Ingrese el valor de %c: ", cola[i].caracter);
        float *v = malloc(sizeof(float));
        scanf("%f", v);
        *(v) = *v;  // asignamos el valor ingresado
        cola[i].valor = v;
    }
}



float evaluarPostfix(Dato *cola, int tam) {
    Pila pila = inicializarPila(100);
    for(int i=0;i<tam;i++){
        Dato actual = cola[i];
        if(actual.valor){
            Dato *n = malloc(sizeof(Dato));
            n->caracter = actual.caracter;
            n->valor = malloc(sizeof(float));
            *(n->valor) = *(actual.valor);
            push(&pila,n);
        } else {
            Dato *b = pop(&pila);
            Dato *a = pop(&pila);
            float res =0;
            switch(actual.caracter){
                case '+': res = *(a->valor)+*(b->valor); break;
                case '-': res = *(a->valor)-*(b->valor); break;
                case '*': res = *(a->valor)**(b->valor); break;
                case '/': res = *(a->valor)/(*(b->valor)); break;
                default:
                printf("valor desconocido");
                break;
            }

            free(a->valor); 
            free(a);
            free(b->valor);
             free(b);
            Dato *r = malloc(sizeof(Dato));
            r->caracter = 'R';
            r->valor = malloc(sizeof(float));
            *(r->valor) = res;
            push(&pila,r);
        }
    }
    
    Dato *resultado = pop(&pila);
    float valorFinal = *(resultado->valor);
    free(resultado->valor); free(resultado);
    return valorFinal;
}





void generarCola(Dato *cola, char *postfix) {
    for(int i=0; postfix[i]; i++){
        cola[i].caracter = postfix[i];
        if(esOperando(postfix[i])){
            cola[i].valor = malloc(sizeof(float));
            printf("Ingrese el valor de %c: ", postfix[i]);
            scanf("%f", cola[i].valor);
        } else {
            cola[i].valor = NULL;
        }
    }
}
















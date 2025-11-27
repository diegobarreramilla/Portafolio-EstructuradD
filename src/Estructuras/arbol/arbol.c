#include "arbol.h"




/*void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
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
                printf(" |      ");
                //printf(" |      ");
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

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}
void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(raiz->izq)
			insertarArbolOrdenado(raiz->izq,dato,comparar);
		else
			raiz->izq = crearNodoA(dato);

        
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}




void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
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
                printf(" |      ");
                //printf(" |      ");
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

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}
void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}



void preorden(NodoA* raiz,void(*imprimir)(void*)){

    if(!raiz )
        return;

    printf(" ");
    ///primero imprime al raiz
    imprimir(raiz->dato);
    ///imprime el dato de hasta la izquierda y regresa
    preorden(raiz->izq,imprimir);
    ///si el el ultimo izquiero se hace el derecho
    preorden(raiz->dch,imprimir);
        


}

void orden(NodoA* raiz,void(*imprimir)(void*)){
    if(!raiz)
        return;

    orden(raiz->izq,imprimir);
    printf(" ");
    imprimir(raiz->dato);
    orden(raiz->dch,imprimir);



}

void inverso(NodoA* raiz,void(*imprimir)(void*)){

    if(!raiz)
        return;

    inverso(raiz->dch,imprimir);
    printf(" ");
    imprimir(raiz->dato);
    inverso(raiz->izq,imprimir);





}

void postorden(NodoA* raiz,void(*imprimir)(void*)){

    if(!raiz)
        return;

    postorden(raiz->izq,imprimir);
    postorden(raiz->dch,imprimir);
    printf(" ");
    imprimir(raiz->dato);




}
void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}

int calcularAltura(NodoA* raiz){
    if(!raiz)
    return 0;

int izq =calcularAltura(raiz->izq);
int dch = calcularAltura(raiz->dch);
        
    return 1+ ((izq>dch) ? izq:dch);
    
}

int Altura(Arbol* arbol){

    if(!arbol)
        return 0;

    return calcularAltura(arbol->raiz);
    

}

void borrarArbol(Arbol* arbol){
    if(!arbol)
    return;

    borrar(arbol->raiz);
    arbol->raiz = NULL;
}

void borrar(NodoA* raiz){

    if(!raiz)
    return;

    borrar(raiz->izq);
    borrar(raiz->dch);
    free(raiz->dato);
    free(raiz);
    

}
NodoA*  buscarDato(Arbol* arbol, int dato){

    if(!arbol->raiz){
        return NULL;
    }
    return buscar(arbol->raiz,dato);


}

NodoA* buscar(NodoA* raiz, int dato){

    if(!raiz)return NULL;
    NodoA *actual = raiz;
    
    ///buscra mientras sea diferente de null
    while(actual){
        ///valor del nodo actual casteado y desreferenciado
        int valor = *(int*)actual->dato;


        if(valor == dato){
                    return actual;
                }

        if(valor>dato){
            actual = actual->izq;
        }else{
            actual = actual->dch;
        }
        ///se encontro
        
    }

    return NULL;

}

void eliminarNodo(Arbol* arbol, int dato) {
    if (!arbol || !arbol->raiz) return;
    eliminar(&arbol->raiz, dato);
    arbol->cantidad--;
}

void eliminar(NodoA **raiz, int dato) {
    if (!raiz || !*raiz) return;

    NodoA **actual = raiz;

    while (*actual) {
        int valor = *(int*)(*actual)->dato;

        if (dato < valor) {
            actual = &((*actual)->izq);
        } else if (dato > valor) {
            actual = &((*actual)->dch);
        } else { // encontrado
            NodoA *nodo = *actual;

            // CASO 1: Hoja
            if (!nodo->izq && !nodo->dch) {
                free(nodo->dato);
                free(nodo);
                *actual = NULL;
                return;
            }

            // CASO 2: Un hijo
            if (!nodo->izq) {
                *actual = nodo->dch;
                free(nodo->dato);
                free(nodo);
                return;
            }
            if (!nodo->dch) {
                *actual = nodo->izq;
                free(nodo->dato);
                free(nodo);
                return;
            }

            // CASO 3: Dos hijos
            // buscamos el sucesor in-order (mínimo del subárbol derecho)
            NodoA **sucesor = &nodo->dch;
            while ((*sucesor)->izq) {
                sucesor = &((*sucesor)->izq);
            }

            // intercambiamos datos
            int *temp = nodo->dato;
            nodo->dato = (*sucesor)->dato;
            (*sucesor)->dato = temp;

            // eliminamos recursivamente el sucesor (que ahora tiene el dato a eliminar)
            eliminar(sucesor, dato);
            return;
        }
    }
}


///funciones de comprar arboles
int Comparar(Arbol* arbol1, Arbol* arbol2){

    ///algun arbol es NULL 
    int resultado;
    if(!arbol1->raiz || !arbol2->raiz)
    return 0;
    
    ///diferentes en estructura r datos
    if(arbol1->cantidad != arbol2->cantidad)
    return 0;

    else
    resultado = compararDatoArbol(arbol1, arbol2);

    return resultado;
    
}

int compararDatoArbol(Arbol* arbol1, Arbol* arbol2){

    ///contienen diferentes datos
    if(arbol1->raiz == NULL|| arbol2->raiz == NULL || arbol1->cantidad != arbol2->cantidad)
        return 0;
    
    int* arreglo1 = malloc((arbol1->cantidad *(sizeof(int))));
    int* arreglo2 = malloc((arbol1->cantidad *(sizeof(int))));
    int i1  =0;
    int i2 =0;

    llenarArregloOrden(arbol1->raiz,arreglo1,&i1);
    llenarArregloOrden(arbol2->raiz,arreglo2,&i2);

    
    int cantidad = arbol1->cantidad;
    int iguales = 1;

    for(int indice =0;indice < cantidad; indice++){
        if(arreglo1[indice] != arreglo2[indice]){
            iguales =0;
            break;
        }

    }


    free(arreglo1);
    free(arreglo2);
    return(iguales==1)? 1:0;

    
}

int Estructura(Arbol* arbol1, Arbol* arbol2){

    return(comparaEstructura(arbol1->raiz, arbol2->raiz));
}

int comparaEstructura(NodoA* raiz1, NodoA* raiz2){
    if(!raiz1 && !raiz2)
    return 1;

    if(!raiz1 || !raiz2)
    return 0;

    int izq = comparaEstructura(raiz1->izq,raiz2->izq);
    int dch = comparaEstructura(raiz1->dch,raiz2->dch);


    if( izq== 1 && dch == 1){
        return 1;
    }
    else 
    return 0;
}

void llenarArregloOrden(NodoA* raiz,int* arreglo, int* indice){

    if(!raiz)
    return;

    llenarArregloOrden(raiz->izq,arreglo, indice);

    arreglo[*indice] = *(int*)raiz->dato;
    (*indice)++;

    llenarArregloOrden(raiz->dch,arreglo,indice);
}

int calcularFactorEquilibrio(NodoA* raiz){

if(!raiz)
    return 0;

int izq =calcularAltura(raiz->izq);
int dch = calcularAltura(raiz->dch);
        
    return dch - izq;



}
int equilibrar(Arbol* arbol){
        int indice =0;
        void** arreglo = (void**)malloc(arbol->cantidad * sizeof(void*));
        int FE;
        if(!arbol->raiz )
        return 0;

        else
        FE = calcularFactorEquilibrio(arbol->raiz);
        
        if(FE>=2 || FE <=-2){
        //llenar arreglo en orden
        
        llenarArregloReconstruccion(arbol->raiz, arreglo, &indice);
        ///liberra arbol viejo
        liberaArbol(arbol);
        ///reconstruir arbol
        arbol->raiz = Reconstruir(arreglo,0,arbol->cantidad-1);
        ///liberar arreglo
        free(arreglo);
        return 1;
        }

        return 0;



}



void liberaArbol(Arbol* arbol){
    if(!arbol)
    return;

    borrarNodos(arbol->raiz);
    arbol->raiz = NULL;
}

void borrarNodos(NodoA* raiz){

    if(!raiz)
    return;

    borrarNodos(raiz->izq);
    borrarNodos(raiz->dch);
    free(raiz);
    

}

NodoA* Reconstruir(void **arreglo, int inicio, int fin){

    if(inicio>fin)
    return NULL;

    int medio = inicio + ( fin - inicio)/2;

    NodoA* nuevaraiz = crearNodoA(arreglo[medio]);

    nuevaraiz->izq = Reconstruir(arreglo, inicio,medio-1);
    nuevaraiz->dch = Reconstruir(arreglo, medio+1,fin);

    return nuevaraiz;


}

void llenarArregloReconstruccion(NodoA* raiz,void** arreglo, int* indice){

    if(!raiz)
    return;

    llenarArregloReconstruccion(raiz->izq,arreglo, indice);

    arreglo[*indice] = raiz->dato;
    (*indice)++;

    llenarArregloReconstruccion(raiz->dch,arreglo,indice);
}
*/


/////____ESTUDIO____


void borrarArbol(Arbol* arbol){
    if(!arbol)
    return;

    borrar(arbol->raiz);
    arbol->raiz = NULL;
}

void borrar(NodoA* raiz){

    if(!raiz)
    return;

    borrar(raiz->izq);
    borrar(raiz->dch);
    
    free(raiz);
    

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
                printf(" |      ");
                //printf(" |      ");
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

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}


void insertarNodo(Arbol* arbol,void* dato){
   
    if(vacio(arbol) == 1){
        arbol->raiz = crearNodoA(dato);

    
    }else{  
        insertarOrdenado(arbol->raiz,dato,arbol->comparar);
    }

}



void insertarOrdenado(NodoA* raiz, void* dato,int (comparar)(void* dato1,void* dato2)){
    ////dato mayor a raiz 
   if(comparar(dato,raiz->dato) <=0){
        ///raiz->izq tiene un dato
        if(raiz->izq != NULL){ 
            ///volvemos a llamar a la funcion
            insertarOrdenado(raiz->izq,dato,comparar);
        }else{
            ///insertamos
            raiz->izq = crearNodoA(dato);
        }
        

   }else{
    ////raiz->dato es mayor al dato nuevo
    if(raiz->dch != NULL){
        insertarOrdenado(raiz->dch,dato,comparar);
    }else{
        raiz->dch = crearNodoA(dato);
    }   

    
   }


   
        

}
/*
void imprimirNivel(NodoA* raiz, int nivel){
    if(!raiz)
        return;

    if(nivel == 1){
        imprimirEntero(raiz->dato);
        printf(" ");
    }else if(nivel > 1){
        imprimirNivel(raiz->izq, nivel-1);
        imprimirNivel(raiz->dch, nivel-1);
    }
}

void recorrerPorNiveles(Arbol* arbol){
    int h = Altura(arbol);
    for(int i = 1; i <= h; i++){
        imprimirNivel(arbol->raiz, i);
    }
}

void preorden(NodoA* raiz){
    if(raiz != NULL){
    imprimirEntero(raiz->dato);
    preorden(raiz->izq);
    preorden(raiz->dch);
    }
}
void Enorden(NodoA* raiz){
    if(raiz != NULL){
        Enorden(raiz->izq);
        imprimirEntero(raiz->dato);
        Enorden(raiz->dch);

    }
}

void PostOrden(NodoA* raiz){
    if(raiz!= NULL){
        PostOrden(raiz->izq);
        PostOrden(raiz->dch);
        imprimirEntero(raiz->dato);

    }
}

void enOrdenInverso(NodoA* raiz){
    if(raiz!= NULL){
        enOrdenInverso(raiz->dch);
        imprimirEntero(raiz->dato);
        enOrdenInverso(raiz->izq);
    }

}*/
/*
int buscar(Arbol* arbol, void* dato,int comparar(void* dato1, void* dato2)){
    if(arbol->raiz != NULL) {
        int resultado = buscarDato(arbol->raiz,dato,comparar);
        return resultado;

    }else{
        return -1;
    }

}

int buscarDato(NodoA* raiz,void* dato,int (comparar)(void* dato1,void* dato2)){
    if(raiz!= NULL){
        if(comparar(dato,raiz->dato) == 1){
             return buscarDato(raiz->dch,dato,comparar);
        }else if(comparar(dato,raiz->dato) == -1){
            return buscarDato(raiz->izq,dato,comparar);
        }else if(comparar(dato,raiz->dato) == 0){
            return 1;

        }

    }
    return 0;

}*/

int Altura(Arbol* arbol){
    if(arbol->raiz != NULL){
        
        
        int resultado = calcularAltura(arbol->raiz);
        return resultado;
    }
    else{
        return 0;
    }
}
int calcularAltura(NodoA* raiz){
    
    if(raiz== NULL)
    return 0;
    
    int izq =(calcularAltura(raiz->izq));
    int dch = (calcularAltura(raiz->dch));

    if(izq>dch)
        return 1+izq;

    if(dch> izq)
        return 1+ dch;
    
    return dch+1;
}

int cantidadNodos(NodoA* raiz){
    if(!raiz){
        return 0;
    }

    int izq = cantidadNodos(raiz->izq);
    int dch = cantidadNodos(raiz->dch);

    return izq+1+dch;
}

int contarNodos(Arbol* arbol){
    if(!vacio(arbol)){

    }  
        return 0;
    

}

int buscaMin(NodoA* raiz){
    if(raiz->izq == NULL){
        return *(int*)raiz->dato;
    }


    return buscaMin(raiz->izq);
}

int min(Arbol*arbol){
    if(!vacio(arbol)){
        return buscaMin(arbol->raiz);
    }else{
        return -1;
    }
}

int buscaMax(NodoA* raiz){
    if(!raiz->dch){
        return *(int*)raiz->dato;
    }

        return buscaMax(raiz->dch);
}

int maximo(Arbol* arbol){
     if(!vacio(arbol)){
        return buscaMax(arbol->raiz);
    }else{
        return -1;
    }
}

int Balanceado(Arbol* arbol){
    if(!vacio(arbol)){
        int resultado = revisarBalenceo(arbol->raiz);
        return resultado;
    }else{
        return -1;
    }
}

int revisarBalenceo(NodoA* raiz){
    if(raiz == NULL)
    return 0;

    int izq = revisarBalenceo(raiz->izq);
    if(izq == -1){
        return -1;
    }
    int dch = revisarBalenceo(raiz->dch);
    if(dch == -1){
        return-1;
    }       

    if(dch == izq +1 || dch+1 == izq || dch == izq){
        return 1 + max (izq,dch);
    }else{
        return -1;
    }

}
/*
int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}*/

/*
int buscarDato(NodoA* raiz,void* dato, int  (comparar)(void* dato1, void* dato2)){
    if(!raiz){
        return 0;
    }

    if(comparar(dato,raiz->dato)==0){
        return 1;
    }
    int izq = buscarDato(raiz->izq,dato,comparar);
    int dch = buscarDato(raiz->dch,dato,comparar);

    if(izq || dch){
        return 1;
    }
    return 0;

}

int Buscar(Arbol* arbol,void* dato, int(comparar)(void* dato,void* dato1)){
    if(!vacio(arbol)){
        return buscarDato(arbol->raiz,dato,comparar);
    }else{
        return 0;
    }

}
    */


int buscarDato(NodoA* raiz,void* dato, int  (comparar)(void* dato1, void* dato2)){

    if(!raiz){
        return 0;
    }
    //dato >raiz
    if(comparar(dato,raiz->dato) == 1){
        return buscarDato(raiz->dch,dato,comparar);
        
    }else if (comparar(dato,raiz->dato) == -1){
        return buscarDato(raiz->izq,dato,comparar);
    }  else{
        return 1;
    }

}
int imparesEncontrados(NodoA* raiz){
    if(!raiz){
        return 0;
    }   

    int actual = (*(int*)raiz->dato % 2 == 1)? 1:0;

    int izq = imparesEncontrados(raiz->izq);
    int dch = imparesEncontrados(raiz->dch);

    return actual+izq+dch;
}

int resultadoArbol(NodoA*raiz){
    if(!raiz){
        return 0;
    }   

    int suma = *(int*)raiz->dato;

    int izq = resultadoArbol(raiz->izq);
    int dch = resultadoArbol(raiz->dch);

    return suma+izq+dch;

}
int sumaArbol(Arbol* arbol){
    if(!vacio(arbol)){
        return resultadoArbol(arbol->raiz);
    }else{
        return 0;
    }

}


int Buscar(Arbol*arbol,void*dato, int(comparar)(void*dato1,void*dato2)){
    if(!vacio(arbol)){
        return  buscarDato(arbol->raiz,dato,comparar);
    }
    return 0;
}

int max(int a , int b){
        if(a>b ){
            return a;
        }  else{
            return b;
        }
}

int cantidadHojas(NodoA* raiz){
    if(!raiz){
        return 0;
    }
    
    if(!raiz->izq && !raiz->dch){
        return 1;
    }
    
    int izq =cantidadHojas(raiz->izq);
    int dch = cantidadHojas(raiz->dch);

    return izq + dch;
}

int contarHojas(Arbol* arbol){
    if(!vacio(arbol)){
        return cantidadHojas(arbol->raiz);
    }
        return 0;
    

}

int vacio(Arbol* arbol){
    if(!arbol->raiz){
        return 1;
    }
    return 0;
}



int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}


/*
void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}*/
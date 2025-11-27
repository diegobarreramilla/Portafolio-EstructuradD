#include "heap.h"
#include <string.h>

Heap inicializarHeap(void(*imprimir)(void*), int (*comparar)(void*,void*)){
	Arbol arbol = (Arbol){NULL,0,NULL,NULL};
	return (Heap){NULL,0,abort,imprimir,comparar,MIN};

}


void insertarHeap(Heap* heap,void* dato){

	void** aux;
	heap->cantidad++;

	while(aux == NULL){
		aux = realloc(heap->arr,sizeof(NodoA*) * heap->cantidad);
	}

	heap->arr = aux;
	heap->arr[heap->cantidad-1] = dato;
	heapify(heap);


}


void eliminarEspecifico(Heap* heap, int indice){
	if(heap->arr[0] == NULL){
		return;

	}

	free(heap->arr[indice]);
	if(indice < heap->cantidad){
		heap->arr[indice] = heap->arr[heap->cantidad-1];
	}
	heap->cantidad--;

	heap->arr = realloc(heap->arr,sizeof(NodoA*) * heap->cantidad);

	heapify(heap);


}


void elimiarEspecifico(Heap* heap, int indice){
	if(!heap->arr[0]){
		printf("NO hay nodos");
	}
	//liveramos el espacio del indice
	free(heap->arr[indice]);

	if(indice<heap->cantidad){
		heap->arr[indice] = heap->arr[heap->cantidad-1];
	}
	//recudicos la cantidad y achicamos el arrglo
	heap->cantidad--;
	heap->arr = realloc(heap->arr, sizeof(NodoA*)* heap->cantidad);
	
	//si eliminamos algo que no era el final se rompia , hacemos heapify actualiza el arbol ahi mismo
	if(indice<heap->cantidad){
		heapify(heap);
	}else{
		///si se elimino el del final solo tenemos que actulziar el arbol
		actualizarArbol(heap);
	}

}


				//el heap y el dato nuevo
void insertarHeap(Heap* heap, void* dato){
	///arreglo de nodos de ARBOL para almacenar los demas
	NodoA **aux;
	heap->cantidad++;
	aux = NULL;

	while(aux == NULL){
		//mientars que aux sea NULL entramos al ciclo 
		///despues auz deja de ser NULL por el realloc y sale
		aux = realloc(heap->arr,sizeof(NodoA*) * heap->cantidad);
	}
	////regresamos el vaor del aux al areglo original
	heap->arr = aux;
	///agregamos el nuevo dato al espacio nuevo
	heap->arr[heap->cantidad-1] =crearNodoA(dato);
	////ya con el dato nuevo hacemos heapify para comodar todo
	heapify(heap);

}


void cambiar(Heap* heap, int p){

	int prioritario =p;
	int hi = HIJO_DERECHO(p);
	int hd = HIJO_DERECHO(p);


	if(hi < heap->cantidad && siCambiar(heap,prioritario,hi)){
		prioritario = hi;
	}

	if(hd < heap->cantidad && siCambiar(heap,prioritario,hd)){
		prioritario = hd;
	}

	if(p != prioritario){
		NodoA* aux = heap->arr[p];
		heap->arr[p] = heap->arr[prioritario];
		heap->arr[prioritario] = aux;
		cambiar(heap,prioritario);
	}

}


void heapify(Heap* heap){
	if(heap->arr[0] == NULL){
		return 0;
	}

	for(int i= (heap->cantidad/2)-1;i>= 0;i--){
		cambiar(heap,i);
	}
}


			//reibe el heap que va a modificar y el indice que debe de evaluar
void cambiar(Heap* heap, int p){
	//// es la variable donde va el min o max
	int prioritario = p;


	//guardamos los indices donde estan lso hijos de p
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
		///revisamos si existe y si se debe de cdambiar con funcion auxiliar
	if(hi< heap->cantidad && siCambiar(heap,prioritario,hi)){
		///lo cambiamos
		prioritario = hi;
	}
	//hacemos los mismo con el otro
	if(hd< heap->cantidad && siCambiar(heap,prioritario,hd)){
		///lo cambiamos
		prioritario = hd;
	}

	///si hubo cambios los cambiamos
	if(prioritario != p){
		NodoA* temp = heap->arr[p];
		heap->arr[p] = heap->arr[prioritario];
		heap->arr[prioritario] = temp;

		cambiar(heap,prioritario);
	}

}

void heapify(Heap* heap){

	//si el heap no se puede
	if(!heap){
		return;
	}

	int i;
	////iniciamos desde el ultimo nodo no hoja del arrego(n/2)-1 hasta 0 y vamos hacia atras

	for(i = (heap->cantidad/2) -1;i>=0;i--){	
		cambiar(heap,i);
	}

}

int siCambiar(Heap* heap,int p, int hijo){

	switch (heap->tipo)
	{
	case MAX:
				//si el dato del hijo es mayor (comparra regresa 1) al dato del indice del padre retornamos 1
			if(heap->comparar(heap->arr[hijo]->dato,heap->arr[p]->dato)>0){
				return 1;
			}
		
		break;

	case MIN:
	//si el dato del hijo es menjor (comparra regresa 1) al dato del indice del padre retornamos 1
			if(heap->comparar(heap->arr[hijo]->dato,heap->arr[p]->dato)<0){
				return 1;
			}
		
		break;

	

	return 0;	

	}	
}

void* procesarraiz(Heap* heap){

	if(heap->arr[0] == NULL){
		return NULL;
	}

	NodoA* raiz = heap->arr[0];

	free(heap->arr[0]);

	heap->arr[0] = heap->arr[heap->cantidad-1];
	heap->arr[heap->cantidad-1] = NULL;
	heap->cantidad--;

	if(heap->cantidad>0){
		heapify(heap);
	}

	return raiz;
}


void* procesarraiz(Heap* heap){
	if(!heap->arr[0]){
		return NULL;
	}
						///guardamos el dato quie contine la raiz
	void* raiz = heap->arr[0]->dato;
	//liberamos el espacio
	free(heap->arr[0]);
	//llevamos el ultimo dato al inicio y restamos 1
	heap->arr[0] = heap->arr[heap->cantidad-1];
	heap->cantidad--;

	if(heap->cantidad>0){
		cambiar(heap,0);
		actualizarArbol(heap);
	}
	return raiz;


}

void elimiarEspecifico(Heap* heap, int indice){
	if(!heap->arr[0]){
		printf("NO hay nodos");
	}
	//liveramos el espacio del indice
	free(heap->arr[indice]);

	if(indice<heap->cantidad){
		heap->arr[indice] = heap->arr[heap->cantidad-1];
	}
	//recudicos la cantidad y achicamos el arrglo
	heap->cantidad--;
	heap->arr = realloc(heap->arr, sizeof(NodoA*)* heap->cantidad);
	
	//si eliminamos algo que no era el final se rompia , hacemos heapify actualiza el arbol ahi mismo
	if(indice<heap->cantidad){
		heapify(heap);
	}else{
		///si se elimino el del final solo tenemos que actulziar el arbol
		actualizarArbol(heap);
	}

}







/*
Heap inicializarHeap(void (*imprimir)(void*),int (*comparar)(void*,void*) )
{
	//creamos un arbol
	Arbol arbol = (Arbol){NULL,0,imprimir,NULL,NULL};
	return (Heap){NULL,0,arbol,imprimir,comparar,MIN};
}

void insertarHeap(Heap *heap, void *dato)
{	//arreglo de *
	NodoA **aux;
	heap->cantidad++;
	aux = NULL;
	while(!aux)//nodoA y cantidad uneva
					///lo que vamos a hacer mas grande 			y su tamano nuevo
		aux = realloc(heap->arr,sizeof(NodoA*)*heap->cantidad);
	heap->arr = aux;///insertar el nuevo nodo en el nuevo espacio disponible
	heap->arr[heap->cantidad-1] = crearNodoA(dato); 
	heapify(heap);
}


void* quitarHeap(Heap *heap)
{
	if(heap->cantidad == 0)
		return NULL;
	heap->cantidad--;
	void *dato = heap->arr[0]->dato;
	free(heap->arr[0]);
	heap->arr[0] = heap->arr[heap->cantidad];
	//DECREMENTAR MEMORIA	
	heap->arr = realloc(heap->arr,sizeof(NodoA*)*heap->cantidad);
	heapify(heap);	
	return dato;
}
*/
/*
void heapMin(Heap *heap,int p)
{
	if( p < 0)
		return;
	int minimo = p;
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
	if( (hi<heap->cantidad) && heap->comparar(heap->arr[hi]->dato,heap->arr[minimo]->dato)<0)
		minimo = hi;
	if( (hd<heap->cantidad) && heap->comparar(heap->arr[hd]->dato,heap->arr[minimo]->dato)<0)
		minimo = hd;
	if( minimo!= p)
	{
		NodoA *aux = heap->arr[p];
		heap->arr[p] = heap->arr[minimo];
		heap->arr[minimo] = aux;
		heapMin(heap,minimo);
	}
	else
		heapMin(heap,p-1);	
}
void heapMax(Heap *heap,int p)
{
	if( p < 0)
		return;
	int maximo = p;
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
	if( (hi<heap->cantidad) && heap->comparar(heap->arr[hi]->dato,heap->arr[maximo]->dato)>0)
		maximo = hi;
	if( (hd<heap->cantidad) && heap->comparar(heap->arr[hd]->dato,heap->arr[maximo]->dato)>0)
		maximo = hd;
	if( maximo!= p)
	{
		NodoA *aux = heap->arr[p];
		heap->arr[p] = heap->arr[maximo];
		heap->arr[maximo] = aux;
		heapMax(heap,maximo);
	}
	else
		heapMax(heap,p-1);	
	
}
void heapify(Heap *heap)
{
	int p = heap->cantidad/2-1;
	switch(heap->tipo)
	{
		case MIN:
			heapMin(heap,p);
			break;
		case MAX:
			heapMax(heap,p);
			break;
	}
}
*/



void actualizarArbol(Heap *heap)
{
	int i,hi,hd;;
	for( i = 0 ; i < heap->cantidad ; i++)
	{		
		hi = HIJO_IZQUIERDO(i);
		hd = HIJO_DERECHO(i);
		heap->arr[i]->izq = (hi<heap->cantidad) ? heap->arr[hi]:NULL;
		heap->arr[i]->dch = (hd<heap->cantidad) ? heap->arr[hd]:NULL;
	}
	if(heap->arr)
	{
		heap->arbol.raiz = heap->arr[0];
		heap->arbol.cantidad = heap->cantidad;
	}
	else 
	{
		heap->arbol.raiz = NULL;
		heap->arbol.cantidad = 0;
	}
}

/*
int siCambiar(Heap *heap,int indice,int hijo)
{
	switch(heap->tipo)
	{
		case MAX:		
			if(heap->comparar(heap->arr[hijo]->dato,heap->arr[indice]->dato)>0)
				return 1;
			break;
		case MIN:		
			if(heap->comparar(heap->arr[hijo]->dato,heap->arr[indice]->dato)<0)
				return 1;
			break;
	}
	return 0;
}
	

void* procesarraiz(Heap* heap){
	if(heap->cantidad ==0){
		return NULL;
	}

	void* raiz = heap->arr[0]->dato;
	//raiz
	free(heap->arr[0]);
	
	heap->arr[0] = heap->arr[heap->cantidad-1];
	heap->cantidad--;

	if(heap->cantidad>0){
		cambiar(heap,0);
		actualizarArbol(heap);
	}

	return raiz;
}
*/
void vaciarHeap(Heap* heap){
	
	for(int i =0; i<heap->cantidad;i++){
		if(heap->arr[i]->dato != NULL){
			///si tiene archivo lo libero
			free(heap->arr[i]->dato);
		}
		//libero el ndo
		free(heap->arr[i]);
	}

	if(heap->arr){
		free(heap->arr);
		heap->arr =NULL;
	}

	heap->cantidad =0;
	heap->arbol.raiz = NULL;
	heap->arbol.cantidad = 0;

	actualizarArbol(heap);
}

void eliminarNodoEspecifico(Heap* heap, int indice){
	if(heap->cantidad ==0 || indice> heap->cantidad){
		printf("ERROR");
		return ;
	}


	free(heap->arr[indice]);
	///movemos el utimo al indice del eliminado
	if(indice< heap->cantidad){
		heap->arr[indice] = heap->arr[heap->cantidad-1];

	}
	heap->cantidad--;
	heap->arr = realloc(heap->arr,sizeof(NodoA*) * heap->cantidad);

	if(indice< heap->cantidad){
		cambiar(heap, indice);
		heapify(heap);
	}else{
		actualizarArbol(heap);
	}


}

						///el indice a modificar
void cambiar(Heap* heap, int p){
	int prioritario = p;
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
	///hijo izquierod debe subir??
	if(hi< heap->cantidad && siCambiar(heap,prioritario,hi)){
		prioritario = hi;
	}

	if(hd < heap->cantidad && siCambiar(heap,prioritario,hd)){
		prioritario = hd;
	}

	if(prioritario != p){
		NodoA* temp = heap->arr[p];
		heap->arr[p] = heap->arr[prioritario];
		heap->arr[prioritario] = temp;
		cambiar(heap,prioritario);
	}

}
/*
void heapify(Heap *heap)
{
	
	if(heap->cantidad == 0){
		return;
	}

	int i;
	for( i = (heap->cantidad / 2) - 1; i >= 0; i--)
	{
		cambiar(heap,i);
	}	

	actualizarArbol(heap);
}	


void heapTipo(Heap *heap,int p)
{
	if( p < 0)
		return;
	int indice = p;
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
	if( (hi<heap->cantidad) && siCambiar(heap,indice,hi))
		indice = hi;
	if( (hd<heap->cantidad) && siCambiar(heap,indice,hd))
		indice = hd;
	if( indice!= p) 
	{
		NodoA *aux = heap->arr[p];
		heap->arr[p] = heap->arr[indice];
		heap->arr[indice] = aux;
		heapTipo(heap,indice);
	}
	else
		heapTipo(heap,p-1);	
}

*/

void imprimirHeap(Heap heap)
{
	if(heap.cantidad == 0){
		return;
	}

	int i;
	for( i = 0; i< heap.cantidad ; i++)
	{
		printf("[%i] ",i);
		heap.imprimir( heap.arr[i]->dato);
	}	
}

Archivo* crearArchivo(char* nombre, int paginas){

	Archivo* nuevo = (Archivo*)malloc(sizeof(Archivo));

	strcpy(nuevo->nombre,nombre);
	nuevo->numPaginas = paginas;

	return nuevo;
}

void imprimirArchivo(void* dato){
	Archivo* a = (Archivo*)dato;
	
	printf("Nombre: %s | Contiene: %i paginas\n",a->nombre,a->numPaginas);	
}

int compararArchivo(void* aa, void* bb){
	Archivo* a = (Archivo*)aa;
	Archivo* b = (Archivo*)bb;

	if(a->numPaginas>b->numPaginas){
		return 1;
	}else if(a->numPaginas<b->numPaginas){
		return -1;
	}else{
		return 0;
	}
}
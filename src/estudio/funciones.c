
#include "hashtable.h"


//para saber si se borro
static int _marca_borrado = 0;
void* BORRADO = &_marca_borrado;


void insertarRaw(void** arr,int tam,int(*foldin)(void*),void* dato,int (*comparar)(void*,void*) ){

    int clave, indice,k=0,nuevo_indice;

    clave = foldin(dato);
    indice = hash(clave,tam);
    nuevo_indice = indice;


    while(arr[nuevo_indice] != NULL){
        k++;
        nuevo_indice = rehash(indice,k,tam);
    }
    arr[nuevo_indice] = dato;

}


void Redimensionar(HashTable* hashtable,int nuevoTam){

    void** arrViejo = hashtable->tabla;
    int tamViejo = hashtable->cant;

    hashtable->tabla = calloc(nuevoTam,sizeof(void*));
    hashtable->tam = nuevoTam;

    for(int i =0; i< tamViejo;i++){
        insertarRaw(hashtable->tabla,hashtable->tam,hashtable->folding,arrViejo[i],hashtable->comparar);
    }



}


int insertarClave(HashTable* hashtable,void* dato){

    if(!validarHashTable(hashtable)){
        return 0;
    }
    int nuevotam;
    float FC = (float)hashtable->cant/(float)hashtable->tam;
    if(FC>=0.6 || FC <= 0.30){   
    nuevotam = hashtable->cant / 0.45;
    redimensaionar(hashtable,nuevotam);
    }

    int clave, indice,k,nuevo_indice;
    clave= hashtable->folding(dato);
    indice = hash(clave,hashtable->tam);

    if(hashtable->tabla[indice] == NULL){
        hashtable->tabla[indice] = dato;
    }else{

        k=0;
        do{ 

            nuevo_indice = rehash(indice,k,hashtable->tam);
            if(hashtable->tabla[nuevo_indice] == BORRADO){
                break;
            }
            k++;
        }while(hashtable->tabla[nuevo_indice] != NULL);
        hashtable->tabla[nuevo_indice] = dato;

    }
    hashtable->cant++;
    return 1;


}


Arbol buscar(HashTable* hashtable,void* dato){

    Arbol resultados;
    resultados.comparar = hashtable->comparar;
    resultados.raiz = NULL;
    resultados.cantidad =0;

    int clave, indice, nuevo_indice,k=0;

    clave = hashtable->folding(dato);
    indice = hash(clave,hashtable->tam);

    if(hashtable->tabla[indice] == NULL){
        return resultados;
    }else{

        k;

        do{

            nuevo_indice = rehash(indice,k,hashtable->tam);

            if(hashtable->tabla[nuevo_indice] != NULL){

                if(hashtable->comparar(hashtable->tabla[nuevo_indice],dato) ==0){
                    insertarNodo(&resultados,dato);

                }
            }


            k++;
        }while(hashtable->tabla[nuevo_indice] != NULL);
        return resultados;

    }

}






void redimensionar(HashTable* hashtable, int nuevoTam){

    void** tablaVieja = hashtable->tabla;
    int tamViejo = hashtable->tam;

    hashtable->tabla = (void**)calloc(nuevoTam,sizeof(void*));
    hashtable->tam = nuevoTam;

    for(int i=0; i<tamViejo;i++){

        insertarRaw(hashtable->tabla,nuevoTam,hashtable->folding,tablaVieja[i],hashtable->comparar);
    }
    free(tablaVieja);

}

int InsertarClave(HashTable* hashtable,void*dato){
    if(validarHashTable(hashtable) == NULL){
        return 0;
    }
    int nuevo_tam = hashtable->tam;

    //ver si tenemos que redimensionar
    float FC = (float)hashtable->cant /(float)hashtable->tam;

    if(FC <= 0.30 ){
        nuevo_tam = hashtable->tam /2;
    }else if(FC >= 0.60 ){
        nuevo_tam = hashtable->cant/0.45;
    }

    if(hashtable->tam != nuevo_tam){
        redimensaionar(hashtable,nuevo_tam);
    }



    int clave,indice,k,nuevo_indice;
    clave = hashtable->folding(dato);
    indice = hash(clave,hashtable->tam);

    if(hashtable->tabla[indice] == NULL){
        hashtable->tabla[indice] = dato;
    }else{
        nuevo_indice = indice;
        k=0;
        while(hashtable->tabla[nuevo_indice] != NULL){
            k++;
            nuevo_indice= rehash(indice,k,hashtable->tam);
        }
        hashtable->tabla[nuevo_indice] = dato;

    }

    hashtable->cant++;
    return 1;

}


void insertarRaw(void** arr,int tam,int (*folding)(void*),void* dato,int(*comparar)(void*,void*)){

  

        int clave, indice,k =0,nuevo_indice;
        clave = folding(dato);
        indice = hash(clave,tam);
        nuevo_indice = indice;

        while(arr[nuevo_indice] != NULL){
            k++;
            nuevo_indice = rehash(indice,k,tam);

        }

        arr[nuevo_indice] =dato;
}

Arbol buscarClave(HashTable* hastable, void* dato, int (*comparar)(void*, void*)){

    Arbol resultados;
    resultados.cantidad =0;
    resultados.raiz = NULL;
    resultados.comparar = hastable->comparar;
    resultados.imprimir = hastable->imprimir;

    int indice,nuevo_indice,k,clave;

    clave = hastable->folding(dato);
    indice = hash(clave,hastable->tam);


    if(hastable->tabla[indice] == NULL){
        return resultados;
    }else{

        k =0;
        do{

            nuevo_indice = rehash(indice,k,hastable->tam);

            if(hastable->tabla[nuevo_indice] != NULL && hastable->tabla[nuevo_indice] != BORRADO){

                    if(hastable->comparar(hastable->tabla[nuevo_indice],dato) ==0){
                        insertarNodo(&resultados,dato);
                    }

            }

            k++;
        }while(hastable->tabla[nuevo_indice] != NULL);
        return resultados;

    }


}






HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
	HashTable hashtable = (HashTable) {NULL,tam,0,NULL,imprimir,comparar};
	while(!hashtable.tabla)
		hashtable.tabla = (void**) calloc(tam,sizeof(void*));
	return hashtable;	
}

int validarHashTable(HashTable *hashtable)
{
	if(!hashtable->tabla)
	{
		printf("\n No se ha reservado espacio");
		return 0;
	}
	if(!hashtable->folding )
	{
		printf("\n No se ha asignado alguna de estas funciones: folding,hash,rehash");
		return 0;		
	}
	if(!hashtable->comparar || !hashtable->imprimir)
	{
		printf("\n No se ha asignado alguna de estas funciones: comparar,imprimir");
		return 0;		
	}
	return 1;	
}

Arbol buscarClave(HashTable* hashtable, void *dato, int (*compararOrden)(void*, void*))
{
    
    Arbol arbolResultados;
	arbolResultados.raiz = NULL;
	arbolResultados.cantidad=0;
	arbolResultados.imprimir = hashtable->imprimir;
	arbolResultados.comparar = hashtable->comparar;

    if(!validarHashTable(hashtable))
        return arbolResultados; 
    
    int clave, indice, nuevo_indice, k;

    clave = hashtable->folding(dato);
    indice = hash(clave, hashtable->tam);

    if(hashtable->tabla[indice] == NULL)
        return arbolResultados;
    else
    {
        k = 0;
        do
        {
            // Sondeo Cuadratico
            nuevo_indice = rehash(indice, k, hashtable->tam);
            
            if(hashtable->tabla[nuevo_indice] != NULL && hashtable->tabla[nuevo_indice] != BORRADO)
            {
                
                if(hashtable->comparar(hashtable->tabla[nuevo_indice], dato) == 0)
                {
        
                    insertarNodo(&arbolResultados, hashtable->tabla[nuevo_indice]); 
                }
            }
            k++;
           
        } while( hashtable->tabla[nuevo_indice] != NULL); 
        
        return arbolResultados;
    }
}

int calcularFC(HashTable* hashtable){
    //cantoidad de elementos / cantidad de datos
    float FC = (float)hashtable->cant / (float)hashtable->tam;

    if(FC>=0.30 && FC <= 0.60){
        return 1;
    }else if(FC > 0.60){
        ///necesitamos expandir el tamanno
        return 1;
    }else 
        return -1;
    

}

int eliminarClave(HashTable* hastable,void* dato){

    if(!validarHashTable(hastable)){
        return 0;
    }

    int clave, indice, nuevo_indice,k=0;

    clave = hastable->folding(dato);
    indice = hash(clave,hastable->tam);


    //sino esta el dato
    if(hastable->tabla[indice] == NULL){
        return 0;
        //si existe el dato
    }else{

        do{
            nuevo_indice = rehash(indice,k,hastable->tam);

            if(hastable->tabla[nuevo_indice] != NULL && hastable->tabla[nuevo_indice] != BORRADO){

                if(hastable->tabla[nuevo_indice] == dato){
                    hastable->tabla[nuevo_indice] = BORRADO;
                    hastable->cant--;
                
                ///mal factor de carga
                    if(calcularFC(hastable) == -1){
                        int nuevotam = hastable->tam /2;
                        redimensionar(hastable, nuevotam);
                    }

                    return 1;
                }
            }


        k++;
        }while(hastable->tabla[nuevo_indice] != NULL);
        return 0;
    }
    

}




int insertarClave(HashTable* hashtable, void *dato)
{
    if(!validarHashTable(hashtable)) return 0;

    if (hashtable->cant >= hashtable->tam * 0.6) {
       
        int nuevoTam = (int)(hashtable->cant / 0.45);
        if (nuevoTam <= hashtable->tam) nuevoTam = hashtable->tam * 2;
        
        redimensionar(hashtable, nuevoTam);
    }
    
    
    int clave = hashtable->folding(dato);
    int indice = hash(clave, hashtable->tam);
    int k = 0;
    int nuevo_indice = indice;

    if(hashtable->tabla[indice] == NULL) {
        hashtable->tabla[indice] = dato;
    } else {
        do {
            k++;
            nuevo_indice = rehash(indice, k, hashtable->tam);
			///revisamo si el espacio no fue borrado
			if(hashtable->tabla[nuevo_indice] == BORRADO){
				break;
			}

        } while( hashtable->tabla[nuevo_indice] != NULL);        
        hashtable->tabla[nuevo_indice] = dato;
    }
    
    hashtable->cant++;
    return 1;       
}
    
void redimensionar(HashTable* hashtable, int nuevoTam) {
    printf("\nTabla reajustada de %d -> a: %d \n", hashtable->tam, nuevoTam);
    
    
    void** tablaVieja = hashtable->tabla;
    int tamViejo = hashtable->tam;

    hashtable->tabla = (void**)calloc(nuevoTam, sizeof(void*));
    hashtable->tam = nuevoTam;
    
    for (int i = 0; i < tamViejo; i++) {
        if (tablaVieja[i] != NULL &&tablaVieja[i] != BORRADO) {
            insertarRaw(hashtable->tabla, hashtable->tam, tablaVieja[i], hashtable->folding, hashtable->comparar);
        }
    }

    free(tablaVieja);
}
    
void insertarRaw(void** tabla, int tam, void* dato, int (*folding)(void*), int (*comparar)(void*, void*)) {
    int clave = folding(dato);
    int indice = hash(clave, tam);
    int k = 0;
    int nuevo_indice = indice;

    
    while (tabla[nuevo_indice] != NULL) {
        k++;
        nuevo_indice = rehash(indice, k, tam);
    }
    tabla[nuevo_indice] = dato;
}



int hash(int clave,int tam)
{
	return clave % tam;
}

int rehash(int indice,int k,int tam)
{
	return (indice+k*k)%tam;
}



void buscarClaveAcumulativo(HashTable* hashtable, void *dato, Arbol* arbolAcumulador)
{
    if(!validarHashTable(hashtable)) return;
    
    int clave = hashtable->folding(dato);
    int indice = hash(clave, hashtable->tam);

    if(hashtable->tabla[indice] == NULL) return;
    
    int nuevo_indice = indice;
    int k = 0;
    do {
        nuevo_indice = rehash(indice, k, hashtable->tam);
        
        if(hashtable->tabla[nuevo_indice] != NULL && hashtable->tabla[nuevo_indice] != BORRADO) {
            // Comparamos iniciales (o lo que diga la tabla)
            if(hashtable->comparar(hashtable->tabla[nuevo_indice], dato) == 0) {
                // INSERTAMOS EN EL ÁRBOL EXISTENTE
                insertarNodo(arbolAcumulador, hashtable->tabla[nuevo_indice]);
            }
        }
        k++;
    } while( hashtable->tabla[nuevo_indice] != NULL); 
}



Arbol imprimirISBM(HashTable* hashtable,int (*comparar)(void*,void*)){

	Arbol arbolResultados;
	arbolResultados.raiz = NULL;
	arbolResultados.cantidad=0;
	arbolResultados.imprimir = hashtable->imprimir;
	arbolResultados.comparar = comparar;


	int indice =0;

	if(!validarHashTable(hashtable))
        return arbolResultados; 
	///insertamos todos al arbol
	while(indice <  hashtable->tam){
        if(hashtable->tabla[indice] != NULL && hashtable->tabla[indice] != BORRADO){
		insertarNodo(&arbolResultados,hashtable->tabla[indice]);
        }
        indice++;
	}

		return arbolResultados;

}





void imprimirHashTabla(HashTable *hashtable)
{
	if(!validarHashTable(hashtable))
		return;
	int i,cont=0;
	for(i = 0; i < hashtable->tam ; i++)
	{
		if(hashtable->tabla[i]!=NULL)
		{
			printf("\n [%d] = ",i);
			hashtable->imprimir(hashtable->tabla[i]);
			cont++;
			if( cont == hashtable->cant)
				break;
		}
		else
			printf("\n [%d] = ",i);
	}		
}


HashTable inicializarHashTable(int tam,int cant,void (*imprimir)(void*),int (*comparar)(void*,void*)){
    HashTable hash = (HashTable){NULL,tam,0,NULL,imprimir,comparar};
    //reservamos espacio para la tabla
    while(!hash.tabla){
                    ////arreglo, de tam y tipo void*
        hash.tabla = (void**)calloc(tam,sizeof(void*));
    }
    return hash;
     
}

int insertarClave(HashTable* hashtable, void* dato){
    if(!validarHashTable(hashtable)){    
        return 0;
    }

    float factorCarga = hashtable->cant / hashtable->tam;
    if(factorCarga >= 0.60){
        int nuevo_tam = (int)(hashtable->cant/0.45);

        if(nuevo_tam <= hashtable->tam){
            nuevo_tam = hashtable->tam*2;
        }


        redimensionar(hash,nuevo_tam);
    }
    

    ///obtemos la clave del dato
    int clave = hashtable->folding(dato);
    ///obtenemos el indice del dato respecto a la clave
    int indice = hash(clave,hashtable->tam);
    
    int k=0;
    int nuevo_indice = indice;
    ///insertamos si esta vacio
    if(hashtable->tabla[indice] == NULL){
        hashtable->tabla[indice] = dato;
    }else{
        
        do
        {
        k++;
        ///indice que ira buscando el NULL
        nuevo_indice = rehash(indice,k,hashtable->tam);

            if(hashtable->tabla[nuevo_indice] == BORRADO){
                break;
            }

       
        } while (hashtable->tabla[nuevo_indice] != NULL);
        ///insertamos el nuevo dato en el prime NULL
        hashtable->tabla[nuevo_indice] = dato;
        

    }
    //aumetamos la cantidad de la tabla
    hashtable->cant++;
    return 1;



}


void redimensaionar(HashTable* hastable,int nuevoTam){
    //hacemos una copia de la tabla vieja
    void** tablaVieja = hastable->tabla;
    int tamViejo = hastable->tam;

    ////agrandamos la tabla 
    hastable->tabla = (void**)calloc(nuevoTam,sizeof(void*));
    hastable->tam = nuevoTam;

    //pasamod los datos de la vieja a la nueva

    for(int i =0;i<tamViejo;i++){
        ////si el espaci de la tabla es un dato lo metemos con insertarArw
        if(hastable->tabla[i]!= NULL && hastable->tabla[i] != BORRADO){
            insertarRaw(hastable->tabla,hastable->tam,tablaVieja[i],hastable->folding,hastable->comparar);
        }

    }
    free(tablaVieja);

}

void insertarRaw(void** tabla, int tamano, void* dato,int (*folding)(void*), int (*comparar)(void*,void*) ){
    
    int clave = folding(dato);
    int indice = hash(clave,tamano);

    int k =0;
    int nuevo_indice = indice;
    while (tabla[nuevo_indice != NULL])
    {
        k++;
        nuevo_indice= rehash(clave,k,tamano);
    }
    tabla[nuevo_indice] = dato;
    

}

Arbol buscarClave(HashTable* hashtable, void* dato, int (*compararOrden)(void*, void*)){
    ///inicializamos el arbol
    Arbol arbolResultado;
    arbolResultado.cantidad =0;
    arbolResultado.raiz = NULL;
    arbolResultado.comparar = hashtable->comparar;
    arbolResultado.imprimir = hashtable->imprimir;


    //validamos la tabla
    if(!validarHashTable(hashtable)){
        return arbolResultado;
    }

    int clave,indice, nuevo_indice,k;

    ///obtenemos la clave y el indice
    clave = hashtable->folding(dato);
    indice = hash(clave, hashtable->tam);

    ////el dato no existe
    if(hashtable->tabla[indice] == NULL){
        return arbolResultado;
        ////
    }else{

        k=0;
        do{
            ///haxcemos rehash y comparamos 
            nuevo_indice = rehash(indice,k,hashtable->tam);
            if(hashtable->tabla[nuevo_indice] != NULL && hashtable->tabla[nuevo_indice] != BORRADO){
                
                if(hashtable->comparar(hashtable->tabla[nuevo_indice],dato) ==0){
                        insertarNodo(&arbolResultado,hashtable->tabla[nuevo_indice]);  
                }
            }
            k++;
        }while(hashtable->tabla[nuevo_indice] != NULL);
        return arbolResultado;
    }

}   

int eliminarClave(HashTable* hastable,void* dato){

    if(!validarHashTable(hastable)){
        return 0;
    }

    int clave, indice, nuevo_indice,k=0;

    clave = hastable->folding(dato);
    indice = hash(clave,hastable->tam);


    //sino esta el dato
    if(hastable->tabla[indice] == NULL){
        return 0;
        //si existe el dato
    }else{

        do{
            nuevo_indice = rehash(indice,k,hastable->tam);

            if(hastable->tabla[nuevo_indice] != NULL && hastable->tabla[nuevo_indice] != BORRADO){

                if(hastable->comparar(hastable->tabla[nuevo_indice],dato ) ==0){
                    hastable->tabla[nuevo_indice] = BORRADO;
                    hastable->cant--;
                
                ///mal factor de carga
                    if(calcularFC(hastable) == -1){
                        int nuevotam = hastable->tam /2;
                        redimensionar(hastable, nuevotam);
                    }

                    return 1;
                }
            }


        k++;
        }while(hastable->tabla[nuevo_indice] != NULL);
        return 0;
    }
    

}

int calcularFC(HashTable* hashtable){
    //cantoidad de elementos / cantidad de datos
    float FC = hashtable->cant / hashtable->tam;

    if(FC>=0.30 && FC <= 0.60){
        return 1;
    }else if(FC > 0.60){
        ///necesitamos expandir el tamanno
        return 1;
    }else if(FC< 0.30){
        ///necsitamos reducir el tamano
        return -1;
    }

}


int insertarClave(HashTable* hashtable, void *dato)
{
    if(!validarHashTable(hashtable)) return 0;

    if (hashtable->cant >= hashtable->tam * 0.6) {
       
        int nuevoTam = (int)(hashtable->cant / 0.45);
        if (nuevoTam <= hashtable->tam) nuevoTam = hashtable->tam * 2;
        
        redimensionar(hashtable, nuevoTam);
    }
    
    
    int clave = hashtable->folding(dato);
    int indice = hash(clave, hashtable->tam);
    int k = 0;
    int nuevo_indice = indice;

    if(hashtable->tabla[indice] == NULL) {
        hashtable->tabla[indice] = dato;
    } else {
        do {
            k++;
            nuevo_indice = rehash(indice, k, hashtable->tam);
			///revisamo si el espacio no fue borrado
			if(hashtable->tabla[nuevo_indice] == BORRADO){
				break;
			}

        } while( hashtable->tabla[nuevo_indice] != NULL);        
        hashtable->tabla[nuevo_indice] = dato;
    }
    
    hashtable->cant++;
    return 1;       
}
    
int eliminarClave(HashTable* hashtable, void *dato)
{
    if(!validarHashTable(hashtable)) return 0;

    int clave = hashtable->folding(dato);
    int indice = hash(clave, hashtable->tam);
    
    // Si está vacío de entrada, no existe
    if(hashtable->tabla[indice] == NULL) return 0;

    int nuevo_indice = indice;
    int k = 0;
    
    do {
        nuevo_indice = rehash(indice, k, hashtable->tam);
        
        // Si encontramos algo y no es borrado
        if (hashtable->tabla[nuevo_indice] != NULL && hashtable->tabla[nuevo_indice] != BORRADO) {
            
            // Comparamos 
            if (hashtable->comparar(hashtable->tabla[nuevo_indice], dato) == 0) {
                
                // qctivamos borrado
                hashtable->tabla[nuevo_indice] = BORRADO;
                hashtable->cant--;
                
                // verificar factor de carga
                if (hashtable->cant > 10 && hashtable->cant < hashtable->tam * 0.3) {
                    int nuevoTam = hashtable->tam / 2;
                    if (nuevoTam > 10) redimensionar(hashtable, nuevoTam);
                }
                
                return 1; 
            }
        }
        k++;
    } while (hashtable->tabla[nuevo_indice] != NULL);

    return 0; // No encontrado
}

#include "hashtable.h"
#include "ctype.h"


//para saber si se borro
static int _marca_borrado = 0;
void* BORRADO = &_marca_borrado;

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

HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
	HashTable hashtable = (HashTable) {NULL,tam,0,NULL,imprimir,comparar};
	while(!hashtable.tabla)
		hashtable.tabla = (void**) calloc(tam,sizeof(void*));
	return hashtable;	
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
        if (tablaVieja[i] != NULL) {
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

Arbol imprimirISBM(HashTable* hashtable,int (comparar)(void*,void*)){

	Arbol arbolResultados;
	arbolResultados.raiz = NULL;
	arbolResultados.cantidad=0;
	arbolResultados.imprimir = hashtable->imprimir;
	arbolResultados.comparar = comparar;


	int indice =0;

	if(!validarHashTable(hashtable))
        return arbolResultados; 
	///insertamos todos al arbol
	while(indice < hashtable->tam){
        if(hashtable->tabla[indice] != NULL && hashtable->tabla[indice] != BORRADO){
		insertarNodo(&arbolResultados,hashtable->tabla[indice]);
        
        }
        indice++;
	}   

		return arbolResultados;

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
            
            if(hashtable->tabla[nuevo_indice] != NULL && hashtable->tabla[nuevo_indice]!= BORRADO)
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
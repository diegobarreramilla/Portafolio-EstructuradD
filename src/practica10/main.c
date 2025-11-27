#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"
#include "../Estructuras/hash/hashtable.h"
#include"Libro.h"

void leerCadena(char* cadena, int tam){
	if (fgets(cadena, tam, stdin) != NULL) {
        //eliminar salto
        size_t len = strlen(cadena);
        if (len > 0 && cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0';
        }
    }
}

void Enorden(NodoA* raiz){
    if(raiz != NULL){
        Enorden(raiz->izq);
        imprimirLibro(raiz->dato);
		printf("\n");
        Enorden(raiz->dch);

    }
}

Arbol inicializarArbolManual(void (*imprimir)(void*), int (*comparar)(void*, void*)) {
    Arbol a;
    a.raiz = NULL;
    a.cantidad = 0;
    a.imprimir = imprimir;
    a.comparar = comparar;
    return a;
}


Arbol BuscarRangoTitulo(HashTable* hastable, char inicio, char fin,int(*comparar)(void*,void*)){

	Arbol resultados;
	resultados.cantidad =0;
	resultados.raiz =NULL;
	resultados.comparar = comparar;
	resultados.imprimir = hastable->imprimir;

	if(!validarHashTable(hastable)){
		return resultados;
	}

	inicio = tolower(inicio);
	fin = tolower(fin);


	for(int i =0;i<hastable->tam;i++){

		if(hastable->tabla[i] != NULL && hastable->tabla[i] !=  BORRADO){
            
            Libro* l = hastable->tabla[i];

			char letra = tolower((unsigned char)l->titulo[0]);
            
			if(letra>= inicio && letra <= fin){
				insertarNodo(&resultados,l);
			}


		}

	}

	return resultados;

}

Arbol BuscarRangoAutor(HashTable* hastable, char inicio, char fin,int(*comparar)(void*,void*)){

	Arbol resultados;
	resultados.cantidad =0;
	resultados.raiz =NULL;
	resultados.comparar = comparar;
	resultados.imprimir = hastable->imprimir;


	if(!validarHashTable(hastable)){
			return resultados;
	}



	inicio = tolower(inicio);
	fin = tolower(fin);

	

	for(int i =0;i<hastable->tam;i++){

		if(hastable->tabla[i] != NULL && hastable->tabla[i] !=  BORRADO){
            
            Libro* l = hastable->tabla[i];

			char letra = tolower((unsigned char)l->autor[0]);
            
			if(letra>= inicio && letra <= fin){
				insertarNodo(&resultados,l);
			}


		}

	}

	return resultados;

}


/*
Arbol buscarRangoTexto(HashTable* tabla, char inicio, char fin, int tipo, int (*compararOrden)(void*, void*)) {
    Arbol resultados = inicializarArbolManual(tabla->imprimir, compararOrden);
    
    inicio = tolower((unsigned char)inicio);
    fin = tolower((unsigned char)fin);
    
    for(int i = 0; i < tabla->tam; i++) {
        if(tabla->tabla[i] != NULL) {
            Libro* l = (Libro*)tabla->tabla[i];
            char letra;
            
            // 1-titulo 2 autor
            if(tipo == 1) letra = tolower((unsigned char)l->titulo[0]);
            else          letra = tolower((unsigned char)l->autor[0]);
            
            if(letra >= inicio && letra <= fin) {
                insertarNodo(&resultados, l);
            }
        }
    }
    return resultados;
}
*/


Arbol buscarRangoFecha(HashTable* tabla, int anioInicio, int anioFin, int (*compararOrden)(void*, void*)) {
    Arbol resultados = inicializarArbolManual(tabla->imprimir, compararOrden);
    
    for(int i = 0; i < tabla->tam; i++) {
        if(tabla->tabla[i] != NULL) {
            Libro* l = (Libro*)tabla->tabla[i];
            if(l->fecha >= anioInicio && l->fecha <= anioFin) {
                insertarNodo(&resultados, l);
            }
        }
    }
    return resultados;
}



int main(void)
{	
	Libro* libros = obtener_libros();
	

	///tabla ISBN
	HashTable tabla_ISBN = inicializarHashTable(100,&imprimirLibro,&compararISBN);
	tabla_ISBN.folding = &foldingISBN;
	
	///tabla Autor
	HashTable tabla_Autores = inicializarHashTable(100,&imprimirLibro,&compararAutor);
	tabla_Autores.folding = &foldingAutor;
	
	///tabla fefha
	HashTable tabla_Fecha = inicializarHashTable(100,&imprimirLibro,&compararAno);
	tabla_Fecha.folding = &foldingfecha;

	///tabla Titulo
	HashTable tabla_Titulo = inicializarHashTable(100,&imprimirLibro,&compararTitulo);
	tabla_Titulo.folding = &foldingTitulo;

	HashTable rango_titulo = inicializarHashTable(100,&imprimirLibro,&compararTitulo);
	rango_titulo.folding = &foldingTitulo;
	

	HashTable rango_autores = inicializarHashTable(100,&imprimirLibro,&compararAutor);
	rango_autores.folding = &foldingAutor;


	
	

	//insertar libros
	for(int i =0;i<CANT_LIBROS;i++){
		insertarClave(&tabla_ISBN,&libros[i]);
		insertarClave(&tabla_Autores,&libros[i]);
		insertarClave(&tabla_Fecha,&libros[i]);
		insertarClave(&tabla_Titulo,&libros[i]);
		insertarClave(&rango_autores,&libros[i]);
		insertarClave(&rango_titulo,&libros[i]);
	}
	///libro para comarar
	Libro generico;
	Libro *eliminar;
	Arbol resultados;
	char cadena[100];
	int opc =-1;
	int opc1 =-1;
	int opc2 =-1;
	int opc3 =-1;
	char inicio;
	char fin;
	int fecha;
	int anoInicio;
	int anoFin;

	///

	char nombre[50];
	char titulo[50];
	int ano =0 ;
	char ISBN [50];

	do{

		printf("\n\n[1] Buscar por ISBN\n");
		printf("[2] Buscar por Titulo\n");
		printf("[3] Buscar por Fecha\n");
		printf("[4] Buscar por Autor\n");
		printf("[5] Eliminar por ISBN\n");
		printf("[6] Imprimir lista ISBN\n");
		printf("[7] Agregar libro\n");
		printf("[8] Salir\n");
		scanf("%i",&opc);
		getchar();

		switch (opc)
		{
		case 1:
		printf("\n\nIntroduzca el ISBN\n\n");
		leerCadena(cadena,50);
		strcpy(generico.isbn,cadena);
		resultados = buscarClave(&tabla_ISBN,&generico,&compararISBN);



		printf("Resultados:");
		if(vacio(&resultados)){
			printf("\nVACIO\n");
		}else{
			Enorden(resultados.raiz);
		}
		//reiniciamos
		borrarArbol(&resultados);

		

			break;
		case 2:

		printf("[1] Buscra por Titulo\n[2] Buscra por rango de iniciales:\n\n" );
		scanf("%i",&opc1);
		getchar();

		if(opc1 == 1){
			printf("INtroduzca el titulo\n");
			leerCadena(cadena,50);
			strcpy(generico.titulo,cadena);
			printf("\nResultados:\n");

			resultados = buscarClave(&tabla_Titulo,&generico,&compararTitulo);

			if(vacio(&resultados)){
				printf("\nVAcio\n");
			}else{
			
			Enorden(resultados.raiz);
			borrarArbol(&resultados);
			}
		}else if(opc1 == 2){
			printf("\nIntroduzca la letra inicial:\n");
			scanf(" %c",&inicio);
			printf("\nIntroduzca la letra final:\n");
			scanf(" %c",&fin);
			
			resultados = BuscarRangoTitulo(&rango_titulo,inicio,fin,&compararTitulo);
			printf("\nResultados:\n");
			if(vacio(&resultados)){
				printf("\nVAcio\n");
			}else{
			
			Enorden(resultados.raiz);
			borrarArbol(&resultados);
			}

		}else{
			printf("\nError\n");
		}
		

			break;
		case 3:

		printf("[1] Buscar por fecha exacta\n[2] Buscar por rango" );
		scanf("%i",&opc2);
		getchar();

		if(opc2 == 1){
			printf("\nIngrese el anio:\n");
			scanf("%i",&fecha);
			generico.fecha = fecha;
			resultados = buscarClave(&tabla_Fecha,&generico,&compararAno);
			
			
			printf("\nResultados:\n");
			if(vacio(&resultados)){
				printf("\nVacio\n");
			}else{
			
			Enorden(resultados.raiz);
			borrarArbol(&resultados);
			}

		}else if (opc2 ==2){
			printf("\nIngrese el ano inicial:\n");
			scanf("%i",&anoInicio);

			printf("\nIngrese el ano final:\n");
			scanf("%i",&anoFin);

			resultados = buscarRangoFecha(&tabla_Fecha,anoInicio,anoFin,&compararTitulo);


			printf("\nResultados:\n");
			if(vacio(&resultados)){
				printf("\nVacio\n");
			}else{
			
			Enorden(resultados.raiz);
			borrarArbol(&resultados);
			}



		}else{
			printf("\nError\n");
		}
		
			
			break;
		case 4:

		printf("[1] Buscar por Nombre exacto\n[2] Buscar por rango de iniciales:" );
		scanf("%i",&opc3);
		getchar();

		if(opc3 ==1){
			printf("\nIntroduzca el Nombre exacto:\n");
			leerCadena(cadena,50);
			strcpy(generico.autor,cadena);


			resultados = buscarClave(&tabla_Autores,&generico,&compararAutor);

			printf("\nResultados:\n");
			if(vacio(&resultados)){
				printf("\nVAcio\n");
			}else{
			
			Enorden(resultados.raiz);
			borrarArbol(&resultados);
			}

		}else if (opc3 ==2){
			
			printf("\nIntroduzca la letra inicial:\n");
			scanf(" %c",&inicio);
			printf("\nIntroduzca la letra final:\n");
			scanf(" %c",&fin);
			
			resultados = BuscarRangoAutor(&rango_autores,inicio,fin,&compararAutor);
			printf("\nResultados:\n");
			if(vacio(&resultados)){
				printf("\nVacio\n");
			}else{
			
			Enorden(resultados.raiz);
			borrarArbol(&resultados);
			}

		}else{
			printf("Error");
		}

			
			break;
		case 5:
		printf("\nIntroduzca el ISBN de libro a elimianr: \n");
		leerCadena(cadena,50);
		strcpy(generico.isbn,cadena);
		printf("\nResultados\n");
		resultados = buscarClave(&tabla_ISBN,&generico,&compararISBN);
		if(vacio(&resultados)){
			printf("\nVacio\n");
		}else{
			eliminar = (Libro*)resultados.raiz->dato;
			printf("\nEliminado\n");
			eliminarClave(&tabla_Autores,eliminar);
			eliminarClave(&tabla_Fecha,eliminar);
			eliminarClave(&tabla_ISBN,eliminar);
			eliminarClave(&tabla_Titulo,eliminar);
			eliminarClave(&rango_autores,eliminar);
			eliminarClave(&rango_titulo,eliminar);
		}
			borrarArbol(&resultados);
			break;

			//imprimir lista completa 
		case 6:

			resultados = imprimirISBM(&tabla_ISBN,&compararTitulo);
			Enorden(resultados.raiz);
			borrarArbol(&resultados);
			
			break;
		////anadir libro	
		case 7:
		printf("\nINtroduzca el nombre del Autor:\n");
		leerCadena(nombre,50);
		
		printf("\nINtroduzca el Titulo del libro:\n");
		leerCadena(titulo,50);
		
		printf("\nIntroduzca la fecha del libro:\n");
		scanf("%i",&ano);
		getchar();
		printf("\nINtroduzca el ISBN:\n");
		leerCadena(ISBN,50);

		
		Libro* nuevo = crearLibro(ISBN,titulo,nombre,ano,1);

		insertarClave(&tabla_Autores,nuevo);
		insertarClave(&tabla_Titulo,nuevo);
		insertarClave(&tabla_Fecha,nuevo);
		insertarClave(&tabla_ISBN,nuevo);
		insertarClave(&rango_autores,nuevo);
		insertarClave(&rango_titulo,nuevo);
		printf("\nLibro incluido correctamente\n");
		

		break;
		
		default:
			break;
		}
		
	

	}while(opc != 8);


	return 0;
}







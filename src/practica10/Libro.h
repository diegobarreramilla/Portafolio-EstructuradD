#ifndef LIBRO_H
#define LIBRO_H

#include <stdio.h>
#include<ctype.h>
#define CANT_LIBROS 50
#define MAX_ISBN 20
#define MAX_TITULO 45
#define MAX_AUTOR 30


typedef struct
{
    char isbn[MAX_ISBN];   //International Standard Book Number
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int fecha;
    int disponible;
}Libro;


Libro* obtener_libros(void);
void imprimirLibro(void* vlibro);



Libro* crearLibro(char* isbn,char* titulo, char* autor,int ano, int disponible);
int compararCadenas(char* cad1, char *cad2);

int foldingString(char* cadena);
int compararISBN(void* LibroA, void* libroB);
int foldingISBN(void* libro);
int compararAno(void* libroA, void* libroB);
int foldingfecha(void* libro);
int compararTitulo(void* LibroA, void* libroB);
int foldingTitulo(void* libro);
int compararAutor(void* LibroA, void* libroB);
int foldingAutor(void* libro);

int foldingInicialTitulo(void* dato) ;
int foldingInicialAutor(void* dato) ;
int compararInicialTitulo(void* libroA, void* libroB);
int compararInicialAutor(void* libroA, void* libroB);

#endif
#include "Libro.h"
#include<string.h>
#include<stdlib.h>


int compararCadenas(char* cad1, char *cad2){
    while (*cad1 && *cad2)
    {
        
        int c1 = tolower((unsigned char)*cad1);
        int c2 = tolower((unsigned char)*cad2);

        if (c1 != c2) {
            return c1 - c2; 
        }
        cad1++;
        cad2++;
    }
    
  
    return tolower((unsigned char)*cad1) - tolower((unsigned char)*cad2);
}

void imprimirLibro(void *vlibro)
{
	if(!vlibro) return;
	Libro *libro = vlibro;
    //printf("%-18s | %-41s | %-25s | %d | %s",libro.isbn, libro.titulo,libro.autor,libro.fecha,libro.disponible);
	printf("%-18s | ",libro->isbn);
	printf("%-41s | ",libro->titulo);
	printf("%-25s | ",libro->autor);
	printf("%d | ",libro->fecha);
	if(libro->disponible)
		printf("DISPONIBLE");
	else
		printf("PRESTADO");
}

Libro* obtener_libros(void)
{
    static Libro libros[CANT_LIBROS] = {
        {"978-3-16-148410-0", "El Quijote", "Miguel de Cervantes", 1605, 1},
        {"978-0-7432-7356-5", "1984", "George Orwell", 1949, 1},
        {"978-0-452-28423-4", "Matar a un ruisenor", "Harper Lee", 1960, 0},
        {"978-0-14-044926-6", "Crimen y castigo", "Fiodor Dostoyevski", 1866, 1},
        {"978-0-307-74118-4", "El gran Gatsby", "F. Scott Fitzgerald", 1925, 0},
        {"978-1-56619-909-4", "Orgullo y prejuicio", "Jane Austen", 1813, 1},
        {"978-0-553-21311-7", "Fahrenheit 451", "Ray Bradbury", 1953, 1},
        {"978-0-553-21311-8", "La Metamorfosis", "Franz Kafka", 1915, 0},
        {"978-0-7434-9757-3", "Los miserables", "Victor Hugo", 1862, 1},
        {"978-0-399-50128-5", "La sombra del viento", "Carlos Ruiz Zafon", 2001, 1},
        {"978-0-8129-8655-4", "Cien anos de soledad", "Gabriel Garcia Marquez", 1967, 1},
        {"978-0-7432-7356-6", "Brave New World", "Aldous Huxley", 1932, 0},
        {"978-0-399-15124-2", "El codigo Da Vinci", "Dan Brown", 2003, 1},
        {"978-0-316-76948-1", "It", "Stephen King", 1986, 0},
        {"978-0-316-76948-2", "El resplandor", "Stephen King", 1977, 1},
        {"978-0-06-112008-4", "El Hobbit", "J.R.R. Tolkien", 1937, 1},
        {"978-0-618-64015-7", "El Senor de los Anillos", "J.R.R. Tolkien", 1954, 1},
        {"978-0-14-028333-4", "Ulises", "James Joyce", 1922, 0},
        {"978-0-7432-7356-7", "Las aventuras de Sherlock Holmes", "Arthur Conan Doyle", 1892, 1},
        {"978-0-307-38926-3", "Dracula", "Bram Stoker", 1897, 0},
        {"978-0-452-28423-5", "Frankenstein", "Mary Shelley", 1818, 1},
        {"978-0-7432-7356-8", "Los juegos del hambre", "Suzanne Collins", 2008, 1},
        {"978-1-4516-7321-1", "Los hombres que no amaban a las mujeres", "Stieg Larsson", 2005, 1},
        {"978-0-7653-4624-8", "Duna", "Frank Herbert", 1965, 0},
        {"978-0-307-28018-2", "La carretera", "Cormac McCarthy", 2006, 1},
        {"978-0-7475-3269-9", "Harry Potter y la piedra filosofal", "J.K. Rowling", 1997, 1},
        {"978-0-7475-3849-3", "Harry Potter y la camara secreta", "J.K. Rowling", 1998, 1},
        {"978-0-7475-4215-6", "Harry Potter y el prisionero de Azkaban", "J.K. Rowling", 1999, 1},
        {"978-0-7475-4624-6", "Harry Potter y el caliz de fuego", "J.K. Rowling", 2000, 1},
        {"978-0-7475-5100-5", "Harry Potter y la Orden del Fenix", "J.K. Rowling", 2003, 0},
        {"978-0-7475-8108-4", "Harry Potter y el misterio del principe", "J.K. Rowling", 2005, 1},
        {"978-0-545-01022-1", "Harry Potter y las Reliquias de la Muerte", "J.K. Rowling", 2007, 1},
        {"978-0-399-15834-6", "El nombre del viento", "Patrick Rothfuss", 2007, 1},
        {"978-0-7564-0714-2", "El temor de un hombre sabio", "Patrick Rothfuss", 2011, 0},
        {"978-0-553-21311-9", "La naranja mecanica", "Anthony Burgess", 1962, 1},
        {"978-0-7432-7356-9", "American Gods", "Neil Gaiman", 2001, 0},
        {"978-0-307-74327-1", "El silencio de los corderos", "Thomas Harris", 1988, 1},
        {"978-0-553-26317-5", "El perfume", "Patrick Suskind", 1985, 0},
        {"978-0-14-243717-9", "Moby Dick", "Herman Melville", 1851, 1},
        {"978-0-307-38927-0", "El cuento de la criada", "Margaret Atwood", 1985, 1},
        {"978-0-00-752550-8", "El problema de los tres cuerpos", "Liu Cixin", 2008, 0},
        {"978-0-14-144167-2", "Grandes esperanzas", "Charles Dickens", 1861, 1},
        {"978-0-7432-7356-1", "El extranjero", "Albert Camus", 1942, 1},
        {"978-0-06-085052-4", "El retrato de Dorian Gray", "Oscar Wilde", 1890, 0},
        {"978-0-618-00221-0", "La historia interminable", "Michael Ende", 1979, 1},
        {"978-0-7432-7356-2", "Los pilares de la Tierra", "Ken Follett", 1989, 1},
        {"978-0-7432-7356-3", "El medico", "Noah Gordon", 1986, 0},
        {"978-0-375-72463-7", "La ladrona de libros", "Markus Zusak", 2005, 1},
        {"978-0-06-231500-7", "Mil soles esplendidos", "Khaled Hosseini", 2007, 0},
        {"978-0-385-35139-2", "La chica del tren", "Paula Hawkins", 2015, 1}
    };
    return &libros[0];    
}

Libro* crearLibro(char* isbn, char* titulo, char* autor, int ano, int disponible){
    Libro* nuevo = calloc(1,sizeof(Libro));

    strcpy(nuevo->isbn,isbn);
    strcpy(nuevo->titulo,titulo);
    strcpy(nuevo->autor,autor);
    nuevo->fecha = ano;
    nuevo->disponible=disponible;

    return nuevo;


}



int foldingString(char* cadena){
    int suma=0;
    int i=0;
    int j =1;

    while(cadena[i] != '\0'){
        ///se hace minuscula, sin signo y se multiplica por la iteracion que vaya ayuda a las colisiones
        suma += tolower((unsigned char)cadena[i]) * j;
        i++;
        j++;

    }
    return suma;


}

int compararISBN(void* LibroA, void* libroB){
    ///castear
    Libro *a = (Libro*)LibroA;
    Libro *b = (Libro*)libroB;
    ///comparar
    
    return compararCadenas(a->isbn,b->isbn);

}

int foldingISBN(void* libro){
    Libro* actual = (Libro*)libro;

    return foldingString(actual->isbn);

}

int compararAno(void* libroA, void* libroB){

    Libro *a = (Libro*)libroA;
    Libro *b = (Libro*)libroB;

    return(a->fecha - b->fecha);
}

int foldingfecha(void* libro){
    Libro* actual = (Libro*)libro;

    return actual->fecha;

}

int compararTitulo(void* LibroA, void* libroB){
    Libro *a = (Libro*)LibroA;
    Libro *b = (Libro*)libroB;
    
    return compararCadenas(a->titulo,b->titulo);

}

int foldingTitulo(void* libro){
    Libro* actual = (Libro*)libro;

    return foldingString(actual->titulo);

}

int compararAutor(void* LibroA, void* libroB){
    Libro *a = (Libro*)LibroA;
    Libro *b = (Libro*)libroB;
    
    return compararCadenas(a->autor,b->autor);
}

int foldingAutor(void* libro){
    Libro* actual = (Libro*)libro;

    return foldingString(actual->autor);

}


int foldingInicialTitulo(void* dato) {
    Libro* l = (Libro*)dato;
   
    return tolower((unsigned char)l->titulo[0]);
}

int foldingInicialAutor(void* dato) {
    Libro* l = (Libro*)dato;
    return tolower((unsigned char)l->autor[0]);
}



int compararInicialTitulo(void* libroA, void* libroB) {
    Libro* a = (Libro*)libroA; 
    Libro* b = (Libro*)libroB; 
    
    char letraA = tolower((unsigned char)a->titulo[0]);
    char letraB = tolower((unsigned char)b->titulo[0]);
    
    return letraA - letraB; 
}

int compararInicialAutor(void* libroA, void* libroB) {
    Libro* a = (Libro*)libroA;
    Libro* b = (Libro*)libroB;
    
    char letraA = tolower((unsigned char)a->autor[0]);
    char letraB = tolower((unsigned char)b->autor[0]);
    
    return letraA - letraB;
}


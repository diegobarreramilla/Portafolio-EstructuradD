cflags = -Wall -Werror -pedantic -std=c99 -O2 -c
dflags = -Wall -Werror -pedantic -std=c99 -g

# Dependencias (si cola depende de nodo.o, se puede añadir aquí)
# En este caso asumo que también necesitas nodos, si no quítalo
sourceNodo = ../nodos/nodo.o  

# Archivos de cola
source = $(wildcard *.c)
source_o = $(wildcard *.o)

# Salida: librería libCola.a en la carpeta lib
output = ../../../lib/libCola.a

build:
	gcc $(cflags) $(source)
	ar rcs $(output) $(source_o) $(sourceNodo)
	@echo "✅ Compilo Exitosamente libCola.a"

clean:
	rm -f $(source_o) $(output)

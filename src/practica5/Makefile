CFLAGS = -Wall -Werror -pedantic -std=c99 -O2
DFLAGS = -Wall -Werror -pedantic -std=c99 -g
INCLUDES = -I ../src/captura -I ../src/Estructuras
LIBS = -L ../../lib -lCaptura -lPila
SOURCE = $(wildcard *.c) ../Estructuras/cola/cola.c
OUTPUT = ../../bin/practica5

build:
	gcc $(CFLAGS) $(SOURCE) -o $(OUTPUT) $(INCLUDES) $(LIBS)
	@echo "✅ Compilado exitosamente!!!"

rebuild:
	$(MAKE) -C ../src/captura
	$(MAKE) -C ../src/Estructuras/nodos
	$(MAKE) -C ../src/Estructuras/cola
	gcc $(CFLAGS) $(SOURCE) -o $(OUTPUT) $(INCLUDES) $(LIBS)
	@echo "✅ Recompilado exitosamente!!!"

run:
	..\..\bin\practica5.exe


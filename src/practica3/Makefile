cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../Estructuras/pila -I ../captura
libs = -L ../../lib -lCaptura -lPila
source = $(wildcard *.c)
output = ../../bin/practica3

build:
	gcc $(cflags) $(includes) $(source) $(libs) -o $(output)
	@echo "Compilo Exitosamente!!!"

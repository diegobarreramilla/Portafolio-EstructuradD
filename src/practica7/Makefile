cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras
libs = ../../lib -lCaptura -lPila
source = $(wildcard *.c) 
output = ../../bin/practica7

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\captura
	make -C ..\Estructuras\nodos
	make -C ..\Estructuras\pila
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	..\..\bin\practica7.exe
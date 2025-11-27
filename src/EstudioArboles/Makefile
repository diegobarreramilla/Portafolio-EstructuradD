cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras
libs = ../../lib -lCaptura -lArbol
source = $(wildcard *.c) 
output = ../../bin/Estudio

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\captura
	make -C ..\Estructuras\nodos
	make -C ..\Estructuras\arbol
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	..\..\bin\Estudio.exe
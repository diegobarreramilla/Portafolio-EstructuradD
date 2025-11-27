cflags = -Wall -Werror -pedantic -std=c99 -O2 -c
dflags = -Wall -Werror -pedantic -std=c99 -g
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../lib/libCaptura.a

build :
	gcc $(cflags) $(source) 
	ar rcs $(output) $(source_o) 
	@echo "Compilo Exitosamente!!!"
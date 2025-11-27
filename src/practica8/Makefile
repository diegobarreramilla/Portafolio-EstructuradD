# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Werror -pedantic -std=c99 -O2

# Flags para debug
DFLAGS = -Wall -Werror -pedantic -std=c99 -g

# Incluye rutas
INCLUDES = -I ../src/captura -I ../src/Estructuras

# Librerías
LIBS = -lCaptura -lPila -lArbol -lCola -L ../../lib

# Archivos fuente
SRC = main.c

# Ejecutable
OUT = ../../bin/practica8

# Regla por defecto
all: build

# Compilación
build:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(INCLUDES) $(LIBS)

# Para debug
debug:
	$(CC) $(DFLAGS) $(SRC) -o $(OUT) $(INCLUDES) $(LIBS)

# Limpiar archivos compilados
clean:
	del $(OUT) 2>nul || rm -f $(OUT)

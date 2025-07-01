CC = gcc

CFLAGS = -Wall -g $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf 

SRC = main.c tablero.c celdas.c
OBJ = main.o tablero.o celdas.o
EXEC = buscaminas

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

tablero.o: tablero.c 
	$(CC) $(CFLAGS) -c tablero.c -o tablero.o

celdas.o: celdas.c 
	$(CC) $(CFLAGS) -c celdas.c

clean:
	rm -f $(OBJ) $(EXEC)


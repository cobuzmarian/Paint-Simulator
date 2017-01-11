# Declaratiile de variabile
CC = g++
CFLAGS = -Wall -lm
SRC = paint_simulator.c
EXE = paint_simulator
 
# Regula de compilare
all:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)
 
# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f $(EXE) *~

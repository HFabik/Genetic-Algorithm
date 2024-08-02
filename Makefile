CC = gcc
CFLAGS = -Wall -lm #-g
EXE = GA
SRC = functions.c OF.c GA.c
 
$(EXE): $(SRC)
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)
 
clean:
	rm -f $(EXE)
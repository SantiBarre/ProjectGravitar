########################################################################
####################### Makefile Template ##############################
########################################################################

CC = gcc
CXXFLAGS = -Wall -std=c99 -pedantic -g
LDFLAGS = -lSDL2 -lm
APPNAME = gravitar

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): main.o dibujado.o figuras.o lista.o polilinea.o nave.o
	$(CC) $(CXXFLAGS) main.o dibujado.o figuras.o lista.o polilinea.o nave.o -o $(APPNAME) $(LDFLAGS)

main.o: main.c config.h figuras.h lista.h polilinea.h
	$(CC) $(CXXFLAGS) -c main.c 

dibujado.o: dibujado.c dibujado.h polilinea.h figuras.h
	$(CC) $(CXXFLAGS) -c dibujado.c

figuras.o: figuras.c figuras.h lista.h polilinea.h
	$(CC) $(CXXFLAGS) -c figuras.c

lista.o: lista.c lista.h 
	$(CC) $(CXXFLAGS) -c lista.c

polilinea.o: polilinea.c polilinea.h 
	$(CC) $(CXXFLAGS) -c polilinea.c

nave.o: nave.c nave.h 
	$(CC) $(CXXFLAGS) -c nave.c

################### Cleaning rules ####################################

clean:
	rm -vf *.o $(APPNAME)

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
$(APPNAME): main.o dibujado.o logica.o figuras.o lista.o polilinea.o nave.o escritura.o caracteres.o disparo.o
	$(CC) $(CXXFLAGS) main.o dibujado.o logica.o figuras.o lista.o polilinea.o nave.o escritura.o caracteres.o disparo.o -o $(APPNAME) $(LDFLAGS)

main.o: main.c dibujado.h figuras.h config.h lista.h polilinea.h nave.h
	$(CC) $(CXXFLAGS) -c main.c 

dibujado.o: dibujado.c dibujado.h polilinea.h figuras.h nave.h config.h
	$(CC) $(CXXFLAGS) -c dibujado.c

logica.o: logica.c logica.h polilinea.h nave.h config.h
	$(CC) $(CXXFLAGS) -c logica.c -lm

figuras.o: figuras.c figuras.h lista.h polilinea.h
	$(CC) $(CXXFLAGS) -c figuras.c

lista.o: lista.c lista.h 
	$(CC) $(CXXFLAGS) -c lista.c

polilinea.o: polilinea.c polilinea.h
	$(CC) $(CXXFLAGS) -c polilinea.c -lm

nave.o: nave.c nave.h config.h polilinea.h
	$(CC) $(CXXFLAGS) -c nave.c 

escritura.o: escritura.c escritura.h caracteres.h
	$(CC) $(CXXFLAGS) -c escritura.c

caracteres.o: caracteres.c caracteres.h
	$(CC) $(CXXFLAGS) -c caracteres.c

disparo.o: disparo.c disparo.h
	$(CC) $(CXXFLAGS) -c disparo.c -lm

################### Cleaning rules ####################################

clean:
	rm -vf *.o $(APPNAME)

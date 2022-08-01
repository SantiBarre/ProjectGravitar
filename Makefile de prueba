########################################################################
####################### Makefile Template ##############################
########################################################################

CC = gcc
CXXFLAGS = -Wall -std=c99 -pedantic -g
LDFLAGS = -lSDL2
APPNAME = gravitar

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): Prueva.o lista.o
	$(CC) $(CXXFLAGS) Prueva.o lista.o -o$(APPNAME) $(LDFLAGS)

Prueva.o: Prueva.c config.h figuras.h lista.h polilinea.h
	$(CC) $(CXXFLAGS) -c Prueva.c 

lista.o: lista.c lista.h
	$(CC) $(CXXFLAGS) -c lista.c

################### Cleaning rules ####################################

clean:
	rm -vf *.o $(APPNAME)

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
$(APPNAME): main.o
	$(CC) $(CXXFLAGS) main.o -o$(APPNAME) $(LDFLAGS)

main.o: main.c config.h
	$(CC) $(CXXFLAGS) -c main.c 


################### Cleaning rules ####################################

clean:
	rm -vf *.o $(APPNAME)

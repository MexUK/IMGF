# Example demonstrating the use of BuildNumber in a Makefile
# Note that buildnumber.h does not have to exist the first
#   time make is executed, since it will be created before
#   hellobuild.c is compiled.
#
# BuildNumber (c) 2006 John M. Stoneham. All rights reserved.
# ----------------------------------------------------------

CC=gcc
CFLAGS=-c -Wall
# Set this to the path where BuildNumber is installed, unless
#   it's already in the search path (don't forget the ending "/")
BNPATH=/usr/local/bin/
BN=$(BNPATH)buildnumber


all: buildnumber hellobuild

hellobuild: hellobuild.o
	$(CC) hellobuild.o -o hellobuild

hellobuild.o: hellobuild.c
	$(CC) $(CFLAGS) hellobuild.c

buildnumber:
	$(BN)

clean:
	rm -f *.o hellobuild
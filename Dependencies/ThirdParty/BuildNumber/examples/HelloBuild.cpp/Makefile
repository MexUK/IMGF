# Example demonstrating the use of BuildNumber in a Makefile
# Note that buildnumber.h does not have to exist the first
#   time make is executed, since it will be created before
#   HelloBuild.cpp is compiled.
#
# BuildNumber (c) 2006 John M. Stoneham. All rights reserved.
# ----------------------------------------------------------

CC=g++
CFLAGS=-c -Wall
# Set this to the path where BuildNumber is installed, unless
#   it's already in the search path (don't forget the ending "/")
BNPATH=/usr/local/bin/
BN=$(BNPATH)buildnumber


all: buildnumber HelloBuild

hellobuild: HelloBuild.o
	$(CC) HelloBuild.o -o HelloBuild

HelloBuild.o: HelloBuild.cpp
	$(CC) $(CFLAGS) HelloBuild.cpp

buildnumber:
	$(BN)

clean:
	rm -f *.o HelloBuild

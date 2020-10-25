SHELL = /bin/bash

# Defining the compiler:
ifeq ($(OS),Windows_NT)
CC = cl
LINK = link
SWITCHES= -nologo -MT -D_CRT_SECURE_NO_DEPRECATE -EHsc -DPTW32_STATIC_LIB
OPTIMIZATION_LEVEL=-O2
DEBUG= #-WX #-pg
OBJECTFLAG =-Fo
COMPILEFLAG =-c
LINK_OPTIONS =-nologo
LINKER_COMMANDS =-out:
LIBRARIES = pthreadVC2S.lib
INCLUDES= -Isrc/distanceCalculation -Isrc/ -Ilib/includes
else
CC = g++
LINK = g++
OPTIMIZATION_LEVEL=-O3 -msse2 -finline-functions -funroll-loops
DEBUG= #-Wall #-g #-pg
OBJECTFLAG =-o
COMPILEFLAG =-c
LIBRARIES =-lpthread
SWITCHES =
LINK_OPTIONS = $(SWITCHES)
LINKER_COMMANDS =-o
INCLUDES=
endif

#CC      = g++
#CFLAGS  = -O3 -finline-functions -funroll-loops -Wall
#LDFLAGS = -lm

SRCPATH=src
OBJPATH=obj
LIBPATH=lib
BINPATH=.

objects = $(OBJPATH)/BLAST2Distance.o \
          $(OBJPATH)/SparseDistanceMatrix.o \
          $(OBJPATH)/FastaSequenceCollection.o \
          $(OBJPATH)/FastaSequence.o \
          $(OBJPATH)/getopt_pp/getopt_pp.o

all: BLAST2Distance

#install:
# Defining the object files:

#clean:
#	rm -fv BLAST2Distance

BLAST2Distance: $(objects)
	$(LINK) $(DEBUG) $(LINK_OPTIONS) $(LINKER_COMMANDS) $(BINPATH)/$@ $+ $(LIBRARIES)

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	$(CC) $(DEBUG) $(SWITCHES) $(OPTIMIZATION_LEVEL) $(INCLUDES) $(COMPILEFLAG) $(OBJECTFLAG) $@ $<

clean:
	-rm $(OBJPATH)/*.o
	-rm $(OBJPATH)/getopt_pp/*.o
	-rm $(BINPATH)/BLAST2Distance

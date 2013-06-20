OBJS = chap8AssortedConceptsInCpp.o
CC = /usr/lib/gcc-snapshot/bin/g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap8AssortedConceptsInCpp.o : chap8AssortedConceptsInCpp.cpp
	$(CC) $(CFLAGS) chap8AssortedConceptsInCpp.cpp

clean:
	\rm *.o *~ p1

OBJS = chap4VirtualFunctions.o
CC = /usr/lib/gcc-snapshot/bin/g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap4VirtualFunctions.o : chap4VirtualFunctions.cpp
	$(CC) $(CFLAGS) chap4VirtualFunctions.cpp

clean:
	\rm *.o *~ p1

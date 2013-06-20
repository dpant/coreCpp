OBJS = chap6Cpp11Features.o
CC = /usr/lib/gcc-snapshot/bin/g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap6Cpp11Features.o : chap6Cpp11Features.cpp
	$(CC) $(CFLAGS) chap6Cpp11Features.cpp

clean:
	\rm *.o *~ p1

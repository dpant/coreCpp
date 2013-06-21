OBJS = chap9LamdaExpressions.o
CC = /usr/lib/gcc-snapshot/bin/g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap9LamdaExpressions.o : chap9LamdaExpressions.cpp
	$(CC) $(CFLAGS) chap9LamdaExpressions.cpp

clean:
	\rm *.o *~ p1

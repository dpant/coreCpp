OBJS = chap5ExplicitAndPartialSpecilization.o
CC = /usr/lib/gcc-snapshot/bin/g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap5ExplicitAndPartialSpecilization.o : chap5ExplicitAndPartialSpecilization.cpp
	$(CC) $(CFLAGS) chap5ExplicitAndPartialSpecilization.cpp

clean:
	\rm *.o *~ p1

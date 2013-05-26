OBJS = chap3OverLoadResolution.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap3OverLoadResolution.o : chap3OverLoadResolution.cpp
	$(CC) $(CFLAGS) chap3OverLoadResolution.cpp

clean:
	\rm *.o *~ p1

OBJS = chap1NameLookup.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap1NameLookup.o : chap1NameLookup.cpp
	$(CC) $(CFLAGS) chap1NameLookup.cpp

clean:
	\rm *.o *~ p1

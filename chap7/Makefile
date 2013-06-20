OBJS = chap7TemplateMetaProgramming.o
CC = /usr/lib/gcc-snapshot/bin/g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap7TemplateMetaProgramming.o : chap7TemplateMetaProgramming.cpp
	$(CC) $(CFLAGS) chap7TemplateMetaProgramming.cpp

clean:
	\rm *.o *~ p1

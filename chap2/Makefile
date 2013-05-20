OBJS = chap2TemplateArgumentDeduction.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

chap2TemplateArgumentDeduction.o : chap2TemplateArgumentDeduction.cpp
	$(CC) $(CFLAGS) chap2TemplateArgumentDeduction.cpp

clean:
	\rm *.o *~ p1

CC = gcc
CFLAGS = -g -Wall #-std=c++14 -Wall
LIBS = -lpthread

EXECS = chap4
OBJS = matrix_mult.o pi-calc.o linked-list.o strtok.o
NP ?= 4

all: ${EXECS}

run: chap4
	./chap4 ${NP}

chap4: main.cpp ${OBJS}
	${CC} ${CFLAGS} -o chap4 main.cpp ${OBJS} ${LIBS}

matrix_mult.o: matrix_mult.cpp matrix_mult.h 
	${CC} ${CFLAGS} -c matrix_mult.cpp ${LIBS}

pi-calc.o: pi-calc.cpp pi-calc.h
	${CC} ${CFLAGS} -c pi-calc.cpp ${LIBS}

linked-list.o: linked-list.cpp linked-list.h 
	${CC} ${CFLAGS} -c linked-list.cpp ${LIBS}

strtok.o: strtok.cpp strtok.h 
	${CC} ${CFLAGS} -c strtok.cpp ${LIBS}

clean:
	rm -f ${EXECS} ${OBJS}
	@echo "all cleaned up!"
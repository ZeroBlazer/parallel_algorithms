CC = gcc
CFLAGS = -g -Wall -fopenmp
LIBS =

EXECS = chap5
OBJS =
NI ?= 100000000000000 
NT ?= 16

all: ${EXECS}

run01: exerc01
	./exerc01 ${NT}

run02: exerc02
	./exerc02 ${NI} ${NT}

exerc01: exerc01.c ${OBJS}
	${CC} ${CFLAGS} -o exerc01 exerc01.c ${OBJS} ${LIBS}

exerc02: exerc02.c ${OBJS}
	${CC} ${CFLAGS} -o exerc02 exerc02.c ${OBJS} ${LIBS}

exerc03: exerc03.c ${OBJS}
	${CC} ${CFLAGS} -o exerc03 exerc03.c ${OBJS} ${LIBS}
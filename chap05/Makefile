CC = gcc
CFLAGS = -g -Wall -fopenmp
LIBS =

EXECS = exerc01.out exerc02.out exerc03.out
OBJS =
NI ?= 10000000000
NT ?= 16

all: ${EXECS}

run01: exerc01.out
	./exerc01.out ${NT}

run02: exerc02.out
	./exerc02.out ${NI} ${NT}

run03: exerc03.out
	./exerc03.out ${NT}

exerc01.out: exerc01.c ${OBJS}
	${CC} ${CFLAGS} -o exerc01.out exerc01.c ${OBJS} ${LIBS}

exerc02.out: exerc02.c ${OBJS}
	${CC} ${CFLAGS} -o exerc02.out exerc02.c ${OBJS} ${LIBS}

exerc03.out: exerc03.c ${OBJS}
	${CC} ${CFLAGS} -o exerc03.out exerc03.c ${OBJS} ${LIBS}

clean:
	rm -f ${EXECS} ${OBJS}
	@echo "all cleaned up!"
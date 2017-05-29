CC = gcc
CFLAGS = -g -Wall -fopenmp
LIBS =

EXECS = chap5
OBJS = 
NT ?= 4

all: ${EXECS}

# run: chap5
# 	./chap5 ${NT}

chap5: exerc01.c ${OBJS}
	${CC} ${CFLAGS} -o chap5 exerc01.c ${OBJS} ${LIBS}

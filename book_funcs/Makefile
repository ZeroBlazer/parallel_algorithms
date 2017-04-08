MPICC = mpicc.mpich
CFLAGS = -g -Wall #-std=c++14 #-Wall
LIBS = #-lstdc++

EXECS = mpi-book
OBJS = trapezoidal.o distribution.o matrix_mult.o sorting.o
NP ?= 4

all: ${EXECS}

run: mpi-book
	mpirun.mpich -n ${NP} ./mpi-book

mpi-book: main.cpp ${OBJS}
	${MPICC} ${CFLAGS} -o mpi-book main.cpp ${OBJS} ${LIBS}

trapezoidal.o: trapezoidal.cpp trapezoidal.h 
	${MPICC} ${CFLAGS} -c trapezoidal.cpp ${LIBS}

distribution.o: distribution.cpp distribution.h 
	${MPICC} ${CFLAGS} -c distribution.cpp ${LIBS}

matrix_mult.o: matrix_mult.cpp matrix_mult.h 
	${MPICC} ${CFLAGS} -c matrix_mult.cpp ${LIBS}

sorting.o: sorting.cpp sorting.h 
	${MPICC} ${CFLAGS} -c sorting.cpp ${LIBS}

clean:
	rm -f mpi-pingpong ${OBJS}
	@echo "all cleaned up!"
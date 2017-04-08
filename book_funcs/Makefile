MPICC = mpicc.mpich
CFLAGS = -g -Wall #-std=c++14 #-Wall
LIBS = #-lstdc++

EXECS = mpi-book
OBJS = trapezoidal.o

all: ${EXECS}

run: mpi-book
	mpirun.mpich -n 2 ./mpi-book

mpi-book: main.cpp ${OBJS}
	${MPICC} ${CFLAGS} -o mpi-book main.cpp ${OBJS} ${LIBS}

trapezoidal.o: trapezoidal.cpp trapezoidal.h 
	${MPICC} ${CFLAGS} -c trapezoidal.cpp ${LIBS}

clean:
	rm -f mpi-pingpong ${OBJS}
	@echo "all cleaned up!"
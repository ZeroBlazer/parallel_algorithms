MPICC = mpicc
CFLAGS = -g -Wall #-std=c++14 #-Wall
LIBS = #-lstdc++

EXECS=mpi-pingpong
#OBJS = #parallel.o linear.o

all: ${EXECS}

run: mpi-pingpong
	mpirun -n 2 ./mpi-pingpong

mpi-pingpong: main.cpp
	${MPICC} ${CFLAGS} -o mpi-pingpong main.cpp ${LIBS}

# parallel.o: parallel.cpp parallel.h 
# 	${CC} ${CFLAGS} -c parallel.cpp ${LIBS}

# linear.o: linear.cpp linear.h 
# 	${CC} ${CFLAGS} -c linear.cpp ${LIBS}

clean:
	rm -f mpi-pingpong ${OBJS}
	@echo "all cleaned up!"
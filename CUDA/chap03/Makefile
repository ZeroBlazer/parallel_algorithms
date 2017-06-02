NVCC = /usr/local/cuda-8.0/bin/nvcc
CFLAGS = 
LIBS = 

EXECS = matrix-mult
#OBJS = #parallel.o linear.o

all: ${EXECS}

run: matrix-mult
	./matrix-mult

matrix-mult: exerc01.cu
	${NVCC} ${CFLAGS} -o matrix-mult exerc01.cu ${LIBS}
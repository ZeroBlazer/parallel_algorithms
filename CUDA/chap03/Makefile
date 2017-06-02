NVCC8 = /usr/local/cuda-8.0/bin/nvcc
NVCC7 = /usr/local/cuda-7.5/bin/nvcc
CFLAGS = 
LIBS = 

EXECS = matrix-mult
#OBJS = #parallel.o linear.o

all: ${EXECS}

run: matrix-mult
	./matrix-mult

matrix-mult: exerc01.cu
	${NVCC7} ${CFLAGS} -o matrix-mult exerc01.cu ${LIBS}
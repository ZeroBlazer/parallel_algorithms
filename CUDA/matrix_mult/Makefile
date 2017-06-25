NVCC8 = /usr/local/cuda-8.0/bin/nvcc
NVCC7 = /usr/local/cuda-7.5/bin/nvcc
CFLAGS = 
LIBS = 

EXECS = matrix-mult.out
OBJS = 

all: ${EXECS}

run: matrix-mult.out
	./matrix-mult.out

matrix-mult.out: matrix_mult.cu
	${NVCC7} ${CFLAGS} -o matrix-mult.out matrix_mult.cu ${LIBS}

clean:
	rm -f ${EXECS} ${OBJS}
	@echo "all cleaned up!"
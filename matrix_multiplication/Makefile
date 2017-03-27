CC = g++
CFLAGS = -std=c++14 #-Wall
LIBS = -lstdc++

OBJS = main.o #parallel.o linear.o

run: matrix-mult
	./matrix-mult

matrix-mult: ${OBJS}
	${CC} ${CFLAGS} -o matrix-mult ${OBJS} ${LIBS}

main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp ${LIBS}

# parallel.o: parallel.cpp parallel.h 
# 	${CC} ${CFLAGS} -c parallel.cpp ${LIBS}

# linear.o: linear.cpp linear.h 
# 	${CC} ${CFLAGS} -c linear.cpp ${LIBS}

clean:
	rm -f matrix-mult ${OBJS}
	@echo "all cleaned up!"
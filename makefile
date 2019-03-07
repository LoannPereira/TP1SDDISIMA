CC = gcc
flags = -Wall -Wextra -pedantic

exe : main.o module.o
	${CC} -o exe main.o module.o ${flags}

main.o : main.c module.h
	${CC} -c main.c ${flags}

module.o : module.c module.h
	${CC} -c module.c ${flags}

clean :
	rm *.o exe

CC = gcc
flags = -Wall -Wextra -pedantic

exe : main.o tp1.o
	${CC} -o exe main.o tp1.o liste_C.o ${flags}

main.o : main.c tp1.c
	${CC} -g -c main.c ${flags}

liste_C.o : tp1.c tp1.h liste_C.c liste_C.h
	${CC} -g -c tp1.c liste_C.c ${flags}

tp1.o : tp1.c tp1.h liste_C.c liste_C.h
	${CC} -g -c tp1.c liste_C.c ${flags}

clean :
	rm *.o exe

all: SBL

SBL: main.o sbl.o
	gcc main.o sbl.o -o SBL -Wall -Wextra -ggdb

main.o: main.c sbl.h
	gcc sbl.o -c -Wall -Wextra -ggdb

sbl.o: sbl.h sbl.c
	gcc sbl.c -c -Wall -Wextra -ggdb

clean:
	rm *.o SBL
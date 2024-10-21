LDFLAGS =-g
CFLAGS = -Wall -Wextra -Wno-unused-parameter
CFLAGS := $(CFLAGS) -Werror

igelArgern : main.o plateau.o testUnitaire.o logique.o
	gcc $(LDFLAGS) $^ -o $@

main.o : main.c plateau.h
	gcc $(CFLAGS) -c $<
	
plateau.o : plateau.c plateau.h
	gcc $(CFLAGS) -c $<

logique.o : logique.c logique.h
	gcc $(CFLAGS) -c $<

testUnitaire.o : testUnitaire.c testUnitaire.h
	gcc $(CFLAGS) -c $<

clean : 
	rm -f main.o plateau.o program testUnitaire.o logique.o
.PHONY: clean 
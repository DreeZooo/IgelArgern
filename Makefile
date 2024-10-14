LDFLAGS =-g
CFLAGS = -Wall -Wextra -Wno-unused-parameter
CFLAGS := $(CFLAGS) -Werror

program : main.o plateau.o
	gcc $(LDFLAGS) $^ -o $@

main.o : main.c plateau.h
	gcc $(CFLAGS) -c $<
	
plateau.o : plateau.c plateau.h
	gcc $(CFLAGS) -c $<

testUnitaire.o : testUnitaire.c testUnitaire.h
	gcc $(CFLAGS) -c $<

clean : 
	rm -f main.o plateau.o program testUnitaire.o
.PHONY: clean 
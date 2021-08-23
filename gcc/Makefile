CFLAGS=-Wall -g -DNDEBUG
#DNDEBUG is for dbg.h debug macros - used to print debug statements - without it, debug printing disappears

%:
	@mkdir -p builds
	gcc $(CFLAGS) $@.c -o ./builds/$@

exercise22:
	@mkdir -p builds
	gcc $(CFLAGS) -c ex22.c -o ./builds/ex22.o
	gcc $(CFLAGS) ex22_main.c builds/ex22.o -o ./builds/ex22_main

cleanall:
		rm -f ./builds/ex*
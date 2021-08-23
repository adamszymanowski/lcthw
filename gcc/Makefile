CFLAGS=-Wall -g -DNDEBUG
#DNDEBUG is for dbg.h debug macros - used to print debug statements - without it, debug printing disappears

%:
	@mkdir -p builds
	gcc $(CFLAGS) $@.c -o ./builds/$@

cleanall:
		rm -f ./builds/ex*
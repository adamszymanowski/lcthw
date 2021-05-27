CFLAGS=-Wall -g

%:
	@mkdir -p builds
	gcc $(CFLAGS) $@.c -o ./builds/$@

cleanall:
		rm -f ./builds/ex*
include ../makefiletmpl


${execs}: %: %.l
	flex -o $@.yy.c $@.l
	gcc $@.yy.c -o $@ -lfl

use-cmdl: cmd1ll.yy.c use-cml1ll.o
	gcc $< -o $@ -lfl

use-cml1ll.o: use-cml1ll.c
	gcc -c $< -o $@

cmd1ll.yy.c: cmdl1.ll
	flex -o $@ $<



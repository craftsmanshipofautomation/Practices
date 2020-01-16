.PHONY: clean
include ./makefiletmpl
##execs = cal1


## from some advanced project
#YACC = bison 
#YFLAGS	= -d -v -t -p nasl
${execs}: %: %.l %.y
	bison -y -d -o $@.tab.c $@.y
	flex -o $@.yy.c $@.l
	gcc -c $@.tab.c $@.yy.c
	gcc $@.tab.o $@.yy.o -o $@ ${CFLAGS}


# use u- prefix to denote those that don't override things
#  they keep things unchanged, for example, yywrap() is not defined manually
${uexecs}: %: %.l %.y
	bison -y -d -o $@.tab.c $@.y
	flex -o $@.yy.c $@.l
	gcc -c $@.tab.c $@.yy.c
	gcc $@.tab.o $@.yy.o -o $@ ${CFLAGS} -ll -lm

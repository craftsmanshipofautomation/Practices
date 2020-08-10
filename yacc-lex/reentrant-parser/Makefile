all: run

parser.c parser.h: parser.y
	bison $^
scanner.c scanner.h: scanner.lex
	flex $^

run: main.c parser.c scanner.c
	gcc -$^ -o $@ -g

clean:
	rm -rf run
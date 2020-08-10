all: clean r

r_parser.c r_parser.h: r_parser.y
	bison $^
r_scanner.c r_scanner.h: r_scanner.lex
	flex $^

r: r.c r2.c r_parser.c r_scanner.c
	gcc $^ -o $@ -g

clean:
	rm -rf r r_parser.c r_parser.h r_scanner.c r_scanner.h
CFLAGS :=  -fsanitize=address -Wall -g
DYN := -lm

exec := exec.o
titles := utils printheap
objects := $(addsuffix .o, ${titles})
other =

all: ${exec} ${objects}
	@gcc -O0 ${exec} ${objects} ${CFLAGS} ${DYN} && ./a.out

${exec}: ${f}
	@gcc -O0 ${CFLAGS} -c ${f} -o $@

${objects}: %.o: %.c %.h ${other}
	@gcc -O0 ${CFLAGS} -c $< -o $@

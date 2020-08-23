CXXFLAGS := -std=c++11
targets := test_aeparser test_matrix_multiplication

define IGNORE
	$(shell echo $1 >>.gitignore)
endef

all: ${targets}
	$(foreach t,${targets},$(call IGNORE,${t}))

test_matrix_multiplication: matrix.hpp \
					array2.hpp \
					complex.hpp \
					complex.cpp \
					utils.hpp \
					test_matrix_multiplication.cpp
	g++ ${CXXFLAGS} -o $@ $^

test_aeparser: aeparser.hpp aeparser.cpp test_aeparser.cpp
	g++ ${CXXFLAGS} -o $@ $^

clean:
	rm ${targets}
	
run:
	./test_aeparser
	./test_matrix_multiplication
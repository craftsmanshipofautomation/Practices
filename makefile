exec_src_d := leetcode massive-data
lib_src_d := lib
out_d := out
cflags := -Wall -g
cxxflags := -std=c++11
libflags := -shared -fpic
lib_cxx_src := $(wildcard ${lib_src_d}/*cpp)
lib_c_src := $(wildcard ${lib_src_d}/*.c)
lib_cxx_header := lib/libcxx.h
lib_c_header := lib/libc.h
lib_d := $(shell pwd)/${out_d}/lib
lib_cxx := ${lib_d}/lib_cxx.so
lib_c := ${lib_d}/lib_c.so

link_load_flags := -Ilib -L${lib_d} -Wl,-rpath=${lib_d}

cxx_src := $(wildcard $(addsuffix *.cpp, $(addsuffix /,${exec_src_d}))) $(wildcard *.cpp)
c_src := $(wildcard $(addsuffix *.c, $(addsuffix /,${exec_src_d}))) $(wildcard *.c)
cxx_execs := ${cxx_src:%.cpp=${out_d}/%}
c_execs   := ${c_src:%.c=${out_d}/%}

all: ${lib_cxx} ${lib_c} ${cxx_execs} ${c_execs}

config:
	@mkdir -p ${lib_d}
	@cd leetcode && /usr/bin/python3.6 generate.py
	$(foreach d,${exec_src_d},$(shell mkdir -p ${out_d}/${d}))

clean:
	@rm out -rf

run:
	@out/${x}

${lib_cxx}: ${lib_cxx_src} ${lib_cxx_header}
	@g++ ${cflags} ${cxxflags} ${libflags} -o $@ $^
${lib_c}: ${lib_c_src} ${lib_header}
	@gcc ${cflags} ${libflags} -o $@ $^

${cxx_execs}: ${out_d}/%: %.cpp ${lib_cxx} ${lib_c}
	@g++ -O0 ${cflags} ${cxxflags} $<  -o $@ ${link_load_flags} -l_cxx

${c_execs}: ${out_d}/%: %.c ${lib_cxx} ${lib_c}
	@gcc -O0 ${cflags} $< -o $@ ${link_load_flags} -l_c -lm
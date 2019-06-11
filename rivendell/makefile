local-dir := rivendell
root-dir := $(shell pwd)/../

out/rivendell/vtable: ${local-dir}/vtable.cpp | out/rivendell
	g++ -std=c++11 -O0 -g -S 

out/rivendell:
	@mkdir -p ${root-dir}/$@
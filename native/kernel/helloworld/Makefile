PWD := $(shell pwd)
obj-m += hello.o

all:
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C ${KERNEL} M=${PWD} modules

clean:
	make -C ${KERNEL} M=${PWD} clean
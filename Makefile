obj-m += code.o

all:
	make -C /lib/modules/5.15.10-arch1-1/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/5.15.10-arch1-1/build M=$(shell pwd) clean


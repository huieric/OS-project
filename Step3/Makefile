	obj-m := myDrive.o
	PWD := $(shell pwd)
	KERNELDIR := /usr/src/linux-headers-4.10.0-28-generic
all:
	make -C $(KERNELDIR) M=$(PWD) modules
.PHONY: clean
clean:
	rm -rf *.o *~ core *.ko *.mod.c modules.order modules.symvers	
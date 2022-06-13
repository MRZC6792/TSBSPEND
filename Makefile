ifneq ($(KERNELRELEASE),)
	obj-m := bsp3.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.c *.cmd *.order *.symvers *.mod .*.*.cmd
endif 

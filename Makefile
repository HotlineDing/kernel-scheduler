obj-m += mysched.o

PWD := $(shell pwd)
KVER := $(shell uname -r)

default:
	make -C /lib/modules/$(KVER)/build SUBDIRS=$(PWD) modules

clean:
	make -C /lib/modules/$(KVER)/build SUBDIRS=$(PWD) clean

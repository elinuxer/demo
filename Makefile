obj-m += helomod.o

all:
	make -C /home/elinux1/projects/at91sam9g35-bsp/buildroot-at91/output/build/linux-linux-3.6.9-at91 M=$(PWD) modules

clean: 
	make -C /home/elinux1/projects/at91sam9g35-bsp/buildroot-at91/output/build/linux-linux-3.6.9-at91  M=$(PWD) clean

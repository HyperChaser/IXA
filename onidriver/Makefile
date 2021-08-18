obj-m+=onidriver.o
all:
	make -C /lib/modules/5.10.0-kali9-amd64/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/5.10.0-kali9-amd64/build/ M=$(PWD) clean

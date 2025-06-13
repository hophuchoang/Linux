EXTRA_CFLAG = -Wall
obj-m = src/cdfile.o

KDIR = /lib/modules/`uname -r`/build

all:
	gcc -o src/app src/app.c
	make -C $(KDIR) M=`pwd` modules

clean:
	rm -rf src/app .vscode
	make -C $(KDIR) M=`pwd` clean
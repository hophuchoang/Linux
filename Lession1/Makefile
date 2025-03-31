stage1:
	gcc -E main.c -o main.i

stage2:
	gcc -S main.i -o main.S

stage3:
	gcc main.S -o main.o

stage4: 
	gcc -o main main.o

all: 
	gcc -o test main.c
clean: 
	rm -rf test a.out

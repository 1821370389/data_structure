main:main.o dynamicArray.o
	gcc main.o dynamicArray.o -o a

main.o:
	gcc -c main.c -o main.o
dynamicArray.o:
	gcc -c dynamicArray.c -o dynamicArray.o

clean:
	@rm -rf *.o a
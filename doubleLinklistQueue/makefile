main:main.o doubleLinkList.o
	gcc main.o doubleLinkList.o -o a
	@rm -rf *.o

main.o:
	gcc -c main.c -o main.o

doubleLinkList.o:
	gcc -c doubleLinkList.c -o doubleLinkList.o

clean:
	@rm -rf a
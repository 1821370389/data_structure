main:main.o doubleLinkList.o doubleLinkListQueue.o binarySearchTree.o
	gcc main.o doubleLinkList.o doubleLinkListQueue.o binarySearchTree.o -o a
	@rm -rf *.o

main.o:
	gcc -c main.c -o main.o

binarySearchTree.o:
	gcc -c binarySearchTree.c -o binarySearchTree.o
doubleLinkList.o:
	gcc -c doubleLinkList.c -o doubleLinkList.o
doubleLinkListQueue.o:
	gcc -c doubleLinkListQueue.c -o doubleLinkListQueue.o

clean:
	@rm -rf a
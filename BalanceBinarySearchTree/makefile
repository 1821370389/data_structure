main:main.o doubleLinkList.o doubleLinkListQueue.o balanceBinarySearchTree.o
	gcc main.o doubleLinkList.o doubleLinkListQueue.o balanceBinarySearchTree.o -o a
	@rm -rf *.o

main.o:
	gcc -c main.c -o main.o

balanceBinarySearchTree.o:
	gcc -c balanceBinarySearchTree.c -o balanceBinarySearchTree.o
doubleLinkList.o:
	gcc -c doubleLinkList.c -o doubleLinkList.o
doubleLinkListQueue.o:
	gcc -c doubleLinkListQueue.c -o doubleLinkListQueue.o

clean:
	@rm -rf a
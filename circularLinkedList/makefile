main:main.o circularLinkList.o
	gcc main.o circularLinkList.o -o a
	@rm -rf *.o

main.o:
	gcc -c main.c -o main.o

circularLinkList.o:
	gcc -c circularLinkList.c -o circularLinkList.o

clean:
	@rm -rf a
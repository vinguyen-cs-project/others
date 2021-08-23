all : tserver tclient
tserver : TCP_Server.o segment.o
	gcc -Wall -o tserver TCP_Server.o segment.o
tclient : TCP_Client.o segment.o
	gcc -Wall -o tclient TCP_Client.o segment.o
TCP_Server.o : TCP_Server.c segment.h
	gcc -Wall -c TCP_Server.c
TCP_Client.o : TCP_Client.c segment.h
	gcc -Wall -c TCP_Client.c
segment.o : segment.c segment.h
	gcc -Wall -c segment.c

clean :
	rm *.out tserver tclient


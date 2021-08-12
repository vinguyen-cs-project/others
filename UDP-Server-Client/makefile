all : userver uclient
userver : UDP_Server.o segment.o
	gcc -Wall -o userver UDP_Server.o segment.o
uclient : UDP_Client.o segment.o
	gcc -Wall -o uclient UDP_Client.o segment.o
UDP_Server.o : UDP_Server.c segment.h
	gcc -Wall -c UDP_Server.c
UDP_Client.o : UDP_Client.c segment.h
	gcc -Wall -c UDP_Client.c
segment.o : segment.c segment.h
	gcc -Wall -c segment.c

clean :
	rm *.out data.txt userver uclient


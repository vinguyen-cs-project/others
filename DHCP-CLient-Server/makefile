all : dserver dclient
dserver : DHCP_Server.o packet.o
	gcc -Wall -o dserver DHCP_Server.o packet.o
dclient : DHCP_Client.o packet.o
	gcc -Wall -o dclient DHCP_Client.o packet.o
DHCP_Server.o : DHCP_Server.c packet.h
	gcc -Wall -c DHCP_Server.c
DHCP_Client.o : DHCP_Client.c packet.h
	gcc -Wall -c DHCP_Client.c
packet.o : packet.c packet.h
	gcc -Wall -c packet.c

clean :
	rm *.o dserver dclient


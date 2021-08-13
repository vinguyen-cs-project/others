/* Vi Nguyen
 * CSCE 3530
 * Client code
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#include "packet.h"


int main(int argc, char* argv[])
{
	//check for user-entered port
	if (argc !=2) {
		fprintf(stderr, "Syntax: dclient <port_number>");
		return 1;
	}
	srand(time(NULL)); //seed time
	struct sockaddr_in si_other;
	int sockfd;

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		perror("socket");
		return 1;
	}
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(atoi(argv[1]));
	if (inet_aton(SERVER , &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		return 1;
	}

    printf("network address (MUST match server): "); //get network address from user
    scanf("%s", netaddr);
	printSend(sockfd, netaddr, stringToBin("0.0.0.0"), rand(), 0, si_other); //send discover packet to server
	packet rPacket;
	memset(&rPacket, 0, sizeof(rPacket));
	recvfrom(sockfd, &rPacket, sizeof rPacket, 0, NULL, NULL); //receive offer packet from server
	printSend(sockfd, netaddr, rPacket.yiaddr, rPacket.tran_ID+1, rPacket.lifetime, si_other); //send request packet to server
	memset(&rPacket, 0, sizeof(rPacket));
	recvfrom(sockfd, &rPacket, sizeof rPacket, 0, NULL, NULL); //receive ack from server
	sleep(3600); //sleep client for 1 hour
	close(sockfd);
	return 0;
}

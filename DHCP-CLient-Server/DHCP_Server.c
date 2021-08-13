/* Vi Nguyen
 * CSCE 3530.002
 * Server Code
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "packet.h"

int main(int argc, char* argv[])
{
	//check for user-entered port
	if (argc !=2) {
		fprintf(stderr, "Syntax: dserver <port_number>\n");
		return 1;
	}
	struct sockaddr_in si_me, si_other;
	int sockfd;
	//create a UDP socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		perror("socket");
		return 1;
	}
	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(atoi(argv[1]));
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	//bind socket to port
	if (bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		perror("bind");
		return 1;
	}

	char netaddr[256];
	unsigned int current, mask, part, max, len = sizeof(si_other);
	printf("network address: "); //get network address from user
	scanf("%s", netaddr);
	printf("subnet_part: "); //get subnet part
	scanf("%u", &part);
	mask = 0xFFFFFFFF<<(32-part); //get subnet mask from subnet part
	current = (stringToBin(netaddr) & mask) + 1; //the first available IP address, do an AND with mask to ensure network bit is 0
	max = (current-1) | ((1<<(32-part))-2); //the last available IP address by doing network address OR 2^(32-part)-2 as .0 and the last IP in range are reserved

	while(current <= max) { //keep track of what IP address is already assigned
		packet rPacket;
		memset(&rPacket, 0, sizeof(rPacket));
		recvfrom(sockfd, &rPacket, sizeof rPacket, 0, (struct sockaddr *) &si_other, &len); //get discover packet from client
		printSend(sockfd, netaddr, current, rPacket.tran_ID+1, 3600, si_other); //send offer packet
		memset(&rPacket, 0, sizeof(rPacket));
		recvfrom(sockfd, &rPacket, sizeof rPacket, 0, (struct sockaddr *) &si_other, &len); //get request packet from client
		printSend(sockfd, netaddr, rPacket.yiaddr, rPacket.tran_ID, rPacket.lifetime, si_other); //send ACK
		current++; //go to next available IP address
	}
	printf("**All IP addresses are taken**\n "); //output message and do nothing when all IPs are assigned
	sleep(3600); //sleep server for an hour
	close(sockfd);
	return 0;
}

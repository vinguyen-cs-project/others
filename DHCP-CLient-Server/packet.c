/* Vi Nguyen
 * CSCE 3530
 * Shared code between server and client
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "packet.h"

unsigned int stringToBin(char* str) { //convert string to IPv4 binary
	struct sockaddr_in tmp;
	memset(&tmp, 0, sizeof(tmp));
	inet_pton(AF_INET, str, &tmp.sin_addr);
	return ntohl(tmp.sin_addr.s_addr);
}

char* binToString(unsigned int bin) { //convert IPv4 binary to string
	struct in_addr sin_addr;
	sin_addr.s_addr=htonl(bin);
	return inet_ntoa(sin_addr);
}
//print and send packet
void printSend(int sockfd, char siaddr[256], unsigned int yiaddr, unsigned int tran_ID, unsigned short int lifetime, struct sockaddr_in si_other) {
	packet sPacket = {stringToBin(siaddr), yiaddr, tran_ID, lifetime};
	printf("Server IP address: %s \nYour IP address: %s \nTransaction ID: %u \nLifetime: %hu \n\n", siaddr, binToString(yiaddr), tran_ID, lifetime); //print to console
    sendto(sockfd, &sPacket, sizeof sPacket, 0, (struct sockaddr *) &si_other, sizeof(si_other));
}

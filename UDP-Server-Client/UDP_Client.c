/* Vi Nguyen
 * CSCE 3530
 * Client code
 * Client cannot know its source port until it sends to server
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "segment.h"

#define SERVER "129.120.151.96"
#define BUFLEN 1024  //Max length of buffer

int main(int argc, char* argv[])
{
	//check for user-entered port
	if (argc !=3) {
		fprintf(stderr, "Syntax: uclient <port> <filename>\n");
		return 1;
	}
	struct sockaddr_in si_other;
	int sockfd;
	unsigned int slen=sizeof(si_other);
	char message[BUFLEN];

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
	//sending internal message to server to get source port info
	sendto(sockfd, "Test", strlen("Test"), 0, (struct sockaddr *) &si_other, slen);
	// SEGMENT PART
	Segment uSegment;
	memset(&uSegment, 0, sizeof(Segment)); //fill struct with 0
	recvfrom(sockfd, &uSegment.sport, sizeof(uSegment.sport), 0, (struct sockaddr *) &si_other, &slen); //populate source field
	sscanf(argv[1], "%hu", &uSegment.dport); //populate destination field
	FILE *file = fopen(argv[2], "r"); //store user input file into buffer
	int x=fread(&message, sizeof(char), BUFLEN, file);
	fclose(file);
	message[x]='\0'; //add null termination
	strcpy(uSegment.data, message); //populate payload field
	uSegment.length = 8 + x; //populate length field
	findCSum(&uSegment); //compute checksum

	//send segment to server
	sendto(sockfd, &uSegment, uSegment.length, 0, (struct sockaddr *) &si_other, slen);
	printWrite("client.out", &uSegment); //print out header fields
	close(sockfd);
	return 0;
}

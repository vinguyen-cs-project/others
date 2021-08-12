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

#include "segment.h"

#define BUFLEN 1024  //Max length of buffer

int main(int argc, char* argv[])
{
	//check for user-entered port
	if (argc !=2) {
		fprintf(stderr, "Syntax: userver <port>\n");
		return 1;
	}
	struct sockaddr_in si_me, si_other;
    int sockfd;
    unsigned int recv_len, slen = sizeof(si_other);
	char buf[BUFLEN];
    
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
    // receive internal message from client to find source port of client
    recv_len = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
    unsigned short port = ntohs(si_other.sin_port); //get source port
    sendto(sockfd, &port, sizeof(port), 0, (struct sockaddr*) &si_other, slen); // send back source p info to client
    
    Segment uSegment;
    unsigned short sum = 0;
    //keep listening for data
	while(1)
	{
		printf("Waiting for data...\n");
		fflush(stdout);
        
		memset(&uSegment, 0, sizeof(Segment));
		//try to receive segment, this is a blocking call
        recv_len = recvfrom(sockfd, &uSegment, sizeof uSegment, 0, (struct sockaddr *) &si_other, &slen);
        sum = uSegment.checksum; //store checksum from client
        uSegment.checksum=0;
        findCSum(&uSegment); //compute new checksum from received segment
        printWrite("server.out", &uSegment); //print out header fields info
        if (sum == uSegment.checksum) {  //checksum matched. no error
            printf("**No error. Saving payload to data.txt file**\n\n");
            FILE *file = fopen("data.txt", "a"); //store payload to txt file
            fprintf(file, "%s\n\n", uSegment.data);
            fclose(file);
        }
        else printf("**Error occurs. Discard segment.**\n\n"); //error
	}
	close(sockfd);
	return 0;
}

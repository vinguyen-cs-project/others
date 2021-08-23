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
#include <time.h>
#include "segment.h"

const int sendS[] = { 0, 2, 3, 6};
int main(int argc, char* argv[])
{
	//check for user-entered port
	if (argc !=2) {
		fprintf(stderr, "Syntax: tclient <port>\n");
		return 1;
	}
	int sockfd;
	struct sockaddr_in servaddr, myaddr;
    char net_addr[256];

	/* AF_INET - IPv4 IP , Type of socket, protocol*/
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(atoi(argv[1])); // Server port number
	//htons convert little to big endian

	/* Convert IPv4 and IPv6 addresses from text to binary form */
    printf("network address: "); //get network address from user
    scanf("%s", net_addr);
	inet_pton(AF_INET,net_addr,&(servaddr.sin_addr));

	/* Connect to the server */
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	getsockname(sockfd, (struct sockaddr *) &myaddr, &(unsigned){sizeof(myaddr)}); //get source port by OS system after connect (computer automatically assign port after connecting)
	srand(time(NULL));
	Segment mSegment, tSegment;
	unsigned short dport;
	sscanf(argv[1], "%hu", &dport);
	int count = 0;
	//create a connection request TCP segment
	memset(&mSegment, 0, 1048); //fill struct with 0
	mSegment.sport = ntohs(myaddr.sin_port); //populate source # field
	mSegment.dport = dport; //populate destination # field
	mSegment.flags=0x6002; //set header length, set SYN bit to 1
	mSegment.seq=6875453;//set random number as sequence
	findtSum(&mSegment); //compute checksum
	printWrite("client.out", &mSegment); //print out header fields to console and client.out
	sendto(sockfd, &mSegment, sizeof mSegment, 0, NULL, NULL); //send created segment to server
	memset(&tSegment, 0, 1048); //fill struct with 0
	recvfrom(sockfd, &tSegment, sizeof tSegment, 0, NULL, NULL); //receive segment from server
	if (checkSum(&tSegment)) {//if checksum matched. no error
		if (tSegment.flags == 0x6012) { //if receive SYNACK segment
			memset(&mSegment, 0, 1048); //fill struct with 0
			mSegment.sport = ntohs(myaddr.sin_port); //populate source # field
			mSegment.dport = dport; //populate destination # field
			mSegment.ack = tSegment.seq +1; //asign server seq +1 to client ack
			mSegment.seq = tSegment.ack; //assign server ack as client seq
			mSegment.flags = 0x6010; //set ACK bit to 1
			findtSum(&mSegment); //compute checksum
			printWrite("client.out", &mSegment); //print out header fields to console and client.out
			sendto(sockfd, &mSegment, sizeof mSegment, 0, NULL, NULL); //send created segment to server
		}
	}
	else printf("**Error occurs. Discard segment.**\n\n"); //error
	memset(&mSegment, 0, 1048); //fill struct with 0
	mSegment.sport = ntohs(myaddr.sin_port); //populate source # field
	mSegment.dport = dport; //populate destination # field
	mSegment.seq = 1024; //set client seq to 1024
	mSegment.ack = 512; //set client ack to 512
	mSegment.flags = 0x6001; //set client FIN bit to 1
	findtSum(&mSegment); //compute checksum
	printWrite("client.out", &mSegment); //print out header fields to console and client.out
	sendto(sockfd, &mSegment, sizeof mSegment, 0, NULL, NULL);
	memset(&tSegment, 0, 1048); //fill struct with 0
	recvfrom(sockfd, &tSegment, sizeof tSegment, 0, NULL, NULL);
	if (checkSum(&tSegment)) {//if checksum matched. no error
		if (tSegment.flags == 0x6010) { //if receive ACK
			memset(&tSegment, 0, 1048); //fill struct with 0
			recvfrom(sockfd, &tSegment, sizeof tSegment, 0, NULL, NULL); //wait for 2nd segment
			if (checkSum(&tSegment)) {//if checksum matched. no error
				if (tSegment.flags == 0x6001) { //if receive FIN
					memset(&mSegment, 0, 1048); //fill struct with 0
					mSegment.sport = ntohs(myaddr.sin_port); //populate source # field
					mSegment.dport = dport; //populate destination # field
					mSegment.ack = tSegment.seq +1; //asign server seq +1 to client ack
					mSegment.seq = tSegment.ack; //assign server ack as client seq
					mSegment.flags = 0x6010; //set ACK bit to 1
					findtSum(&mSegment); //compute checksum
					printWrite("client.out", &mSegment); //print out header fields to console and client.out
					sendto(sockfd, &mSegment, sizeof mSegment, 0, NULL, NULL); //send created segment to server
					sleep(2);
				}
			}
			else printf("**Error occurs. Discard segment.**\n\n"); //error
		}
    }
    else printf("**Error occurs. Discard segment.**\n\n"); //error
    close(sockfd);
    return 0;
}

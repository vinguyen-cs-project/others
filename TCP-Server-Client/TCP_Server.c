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
#include <time.h>
#include "segment.h"

int main(int argc, char* argv[])
{
	//check for user-entered port
	if (argc !=2) {
		fprintf(stderr, "Syntax: tserver <port>\n");
		return 1;
	}
	int listen_fd, conn_fd;
	struct sockaddr_in servaddr;

	/* AF_INET - IPv4 IP , Type of socket, protocol*/
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1])); //htons convert little to big endian
	//force socket to bind to port
	int flag = 1;
	if (setsockopt (listen_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &flag, sizeof(flag))) {
		perror("setsockopt");
		return 1;
	}
	/* Binds the above details to the socket */
	bind(listen_fd,  (struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("TCP Server %d \n\n", atoi(argv[1]));
	/* Start listening to incoming connections */
	listen(listen_fd, 10);

	/* Accepts an incoming connection */
	conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
    Segment tSegment, mSegment;
	int count = 0;
    srand(time(NULL));
	//keep listening for data
	while(1)
	{
		fflush(stdout);
		memset(&tSegment, 0, 1048);
		//try to receive segment, this is a blocking call
		recvfrom(conn_fd, &tSegment, sizeof tSegment, 0, NULL, NULL);
		if (checkSum(&tSegment)) {  // ifchecksum matched. no error
            if (tSegment.flags == 0x6002 || tSegment.flags == 0x6001) { //if receive SYN segment or FIN segment
                memset(&mSegment, 0, 1048); //zero new segment
                mSegment.sport = tSegment.sport; //populate new source port
                mSegment.dport = tSegment.dport; //populate new destination port
                mSegment.ack=tSegment.seq+1; //assign client seq +1 as server ack
                if (tSegment.flags == 0x6002) { //if receive SYN segment
                    mSegment.seq=2935213; //asign random value for server seq
                    mSegment.flags = 0x6012; //set SYN and ACK bits to 1
                }
                else { //if receive FIN segment
                    mSegment.seq = 512; //set server seq as 512
                    mSegment.flags = 0x6010; //set ACK bit to 1
                    findtSum(&mSegment); //compute  checksum
                    printWrite("server.out", &mSegment); //print out header fields info
                    sendto(conn_fd, &mSegment, sizeof mSegment, 0, NULL, NULL); //send ACK segment to client
                    memset(&mSegment, 0, 1048);
                    memset(&mSegment, 0, 1048); //zero new segment
                    mSegment.sport = tSegment.sport; //populate new source port
                    mSegment.dport = tSegment.dport; //populate new destination port
                    mSegment.seq = 512; //set server seq as 512
                    mSegment.ack=tSegment.seq+1; //assign client seq +1 as server ack
                    mSegment.flags = 0x6001; //set FIN bit to 1
                }
                findtSum(&mSegment); //compute checksum
                printWrite("server.out", &mSegment); //print out header fields info
                sendto(conn_fd, &mSegment, sizeof mSegment, 0, NULL, NULL); //send segment to client
            }
            else if (tSegment.flags == 0x6010) { //if receive ACK segment
                if (!count) { //first ACK is for establishing connection
                    printLine("server.out", "**Connection established**");
                    count=1;
                }
                else { //second ACK is for closing connection
                    printLine("server.out", "**Connection closed**");
                    break;
                }
            }
        }
        else printf("**Error occurs. Discard segment.**\n\n"); //error
	}
	close(listen_fd);
	return 0;
}

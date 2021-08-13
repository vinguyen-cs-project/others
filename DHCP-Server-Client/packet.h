/* Vi Nguyen
 * CSCE 3530
 * Header file
 */
#ifndef packet_h
#define packet_h

typedef struct { //packet struct
	unsigned int siaddr, yiaddr, tran_ID;
	unsigned short int lifetime;
} packet;
unsigned int stringToBin(char* str); //convert string to IPv4 binary
char* binToString(unsigned int bin); //convert IPv4 binary to string
void printSend(int sockfd, char siaddr[256], unsigned int yiaddr, unsigned int tran_ID, unsigned short int lifetime, struct sockaddr_in si_other); //print and send packet

#endif

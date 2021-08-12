/* Vi Nguyen
 * CSCE 3530
 * Shared code between server and client
 */
#include <string.h>
#include <stdio.h>

#include "segment.h"

//compute checksum
void findtSum(Segment *tSegment) {
    unsigned short arr[524]; //max length of segment will be 1024 bit data +6*32 bit header = 1048 bits, and we're convering 8 bit to 16 bit here -> element decrease by half
    unsigned int sum = 0;
    memset(arr, 0, 1048);
    memcpy(arr, tSegment, 524);
    for (int i = 0; i < 524; i++) //add all array element
        sum += arr[i];
    while (sum > 65535) { //while sum still larger than 16 bit
        sum = (sum >> 16) + (sum & 0xFFFF); //add carrier and 16 rightmost bit
    }
    tSegment->checksum = ~sum; //flip to get checksum
}

//print out segment to console and file
void printWrite(char name[1024], Segment *tSegment) {
    FILE *file = fopen(name, "a");
    fprintf(file, "Source #: %hu \nDestination #: %hu \nSequence Number: %i \nAcknowledgement Number: %i \nLength: %hu \nFlags (ACK, SYN, FIN): %i, %i, %i \nChecksum: %hu \n\n", tSegment->sport, tSegment->dport, tSegment->seq, tSegment->ack, (tSegment->flags)>>12, ((tSegment->flags)>>4)&0x0001, ((tSegment->flags)>>1)&0x0001, tSegment->flags&0x0001, tSegment->checksum); //print to .out file
    printf("Source #: %hu \nDestination #: %hu \nSequence Number: %i \nAcknowledgement Number: %i \nLength: %hu \nFlags (ACK, SYN, FIN): %i, %i, %i \nChecksum: %hu \n\n", tSegment->sport, tSegment->dport, tSegment->seq, tSegment->ack, (tSegment->flags)>>12, ((tSegment->flags)>>4)&0x0001, ((tSegment->flags)>>1)&0x0001, tSegment->flags&0x0001, tSegment->checksum); //print to console
    fclose(file);
}

int checkSum(Segment *tSegment) {
    unsigned short sum;
    sum = tSegment->checksum;
    tSegment->checksum = 0;
    findtSum(tSegment); //compute new checksum from received segment
    return (tSegment->checksum == sum)? 1 : 0;
}

void printLine(char name[1024], char buf[1024]) {
    FILE *file = fopen(name, "a");
    printf("%s\n\n", buf);
    fprintf(file, "%s\n\n", buf);
    fclose(file);
}

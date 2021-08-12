/* Vi Nguyen
 * CSCE 3530
 * Shared code between server and client
 */
#include <string.h>
#include <stdio.h>

#include "segment.h"

//compute checksum
void findCSum(Segment *uSegment) {
    unsigned short arr[516]; //max length of segment will be 1024+8=1032, and we're convering 8 bit to 26 bit here -> element decrease by half
    unsigned int sum = 0;
    memset(arr, 0, 1032);
    memcpy(arr, uSegment, uSegment->length);
    for (int i = 0; i < 516; i++) //add all array element
        sum += arr[i];
    while (sum > 65535) { //while sum still larger than 16 bit
        sum = (sum >> 16) + (sum & 0xFFFF); //add carrier and 16 rightmost bit
    }
    uSegment->checksum = ~sum; //flip to get checksum
}
//print out segment
void printWrite(char name[1024], Segment *uSegment) {
    FILE *file = fopen(name, "a");
    fprintf(file, "Source: %hu \nDestination: %hu \nLength: %hu \nChecksum: %hu \n \n\n", uSegment->sport, uSegment->dport, uSegment->length, uSegment->checksum); //print to .out file
    printf("Source: %hu \nDestination: %hu \nLength: %hu \nChecksum: %hu \n", uSegment->sport, uSegment->dport, uSegment->length, uSegment->checksum); //print to console
    fclose(file);
}

/* Vi Nguyen
* CSCE 3530
* Header file
*/
#ifndef segment_h
#define segment_h

typedef struct { //segment struct
    unsigned short sport, dport, flags, recv, checksum, ptr;
    unsigned int seq, ack, opt;
    char data[1024];
} Segment;
void findtSum(Segment *tSegment);
void printWrite(char name[1024], Segment *tSegment);
int checkSum(Segment *tSegment);
void printLine(char name[1024], char buf[1024]);
#endif

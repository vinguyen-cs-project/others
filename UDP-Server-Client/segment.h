/* Vi Nguyen
* CSCE 3530
* Header file
*/
#ifndef segment_h
#define segment_h

typedef struct { //segment struct
    unsigned short sport, dport, length, checksum;
    char data[1024];
} Segment;
void findCSum(Segment *uSegment);
void printWrite(char name[1024], Segment *uSegment);

#endif

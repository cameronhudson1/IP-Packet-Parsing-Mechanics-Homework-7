#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _BSD_SOURCE
#include <stdint.h>
#include <endian.h>


/*
Program to parse data from a text file including IP packet data

Parse:
1. Version
2. IHL (Header Length)
3. Type of Service (TOS)
4. Total Length
5. Identification
6. IP Flags(**note**)
7. Fragment Offset
8. Time To Live (TTL)
9. Protocol
10. Header Checksum
11. Source Address
12. Destination Address

*/

typedef struct packetData{
	unsigned char version:4;
	unsigned char ihl:4;
	unsigned char tos:8;
	unsigned int totalLength:16;
	unsigned int identification:16;
	unsigned char flags:3;
	unsigned int fragmentOffset:13;
	unsigned char ttl:8;
	unsigned char protocol:8;
	unsigned int headerChecksum:16;
	unsigned int sourceAddress:16;
	unsigned char* ipAddress;
} packetData;

void printPacket(packetData* packet, number){
	printf("==>Packet %d", number);
}

packetData* parsePacket(FILE* fp){
	packetData* packet = malloc(sizeof(packetData));
	
}

packetData** parseData(FILE* fp){
	//Get number of packets
	int packets;
	fread(&packets, 4, 1, fp);
	
	//Make an array to hold pointers to all packets
	packetData** allPackets = malloc(packets);
	
	for(int i = 0; i < packets; i++){
		allPackets[i] = parsePacket(fp);
	}
	
	for(int i = 0; i < packets; i++){
		printPacket(allPackets[i], i);
	}
}

int main(int argc, char **argv){
	if(argc > 1 && argc < 3){		//1 command line args
		FILE *fp;
		if((fp = fopen(argv[1], "rb")) == NULL){
			packetData** packets = parseData(fp);
		}
		else{
			fprintf(stderr, "An invalid file was input\n");
		}		
	}
	else{							//Not enough or too many command line args
		fprintf(stderr, "Invalid number of command line arguments\n");
	}
	return 0;
}

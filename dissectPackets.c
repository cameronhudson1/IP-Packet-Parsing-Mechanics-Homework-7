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

/*
--------------------------------------------------------------------------
	packetData
		Struct to define the fields of a packet
--------------------------------------------------------------------------
*/
typedef struct packetData{
	int length;
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
} packetData;


/*
--------------------------------------------------------------------------
	printPacket
		Given a pointer to a packetData object, printPacket prints it in a
		readable format
--------------------------------------------------------------------------
*/
void printPacket(packetData* packet, int number){
	printf("==>Packet %d", number);
}


/*
---------------------------------------------------------------------------
	parsePacket(FILE* fp)
		Parses the packet located where the file pointer points
---------------------------------------------------------------------------
*/
packetData* parsePacket(FILE* fp){
	packetData* packet = malloc(sizeof(packetData));
	
	//Read the size of the packet
	fread(&(packet->length), sizeof(int), 1, fp);	//Read byte length of packet
	
	//Read relevant Data from packet
	char importantData[20];
	fread(&importantData, 20, 1, fp);
	
	//Iterate over useless data (me_irl)
	if((packet->length) - 20 > 0){
		char uselessData[(packet->length)-20];
		fread(&uselessData, (packet->length)-20, 1, fp);	
	}
	
	packet->version = ((importantData[0] & 0xF0) >> 4);
	packet->ihl = ;
	packet->tos = ;
	packet->totalLength = ;
	packet->identification = ;
	packet->flags = ;
	packet -> fragmentOffset = ;
	packet->ttl = ;
	packet->protocol = ;
	packet->headerChecksum = ;
	packet->sourceAddress = ;

	return packet;
}


/*
---------------------------------------------------------------------------
	parseData(FILE* fp)
		Parses the data from a file into an array of packet pointers
---------------------------------------------------------------------------
*/
packetData** parseData(FILE* fp){
	//Get number of packets
	int packets;
	fread(&packets, 4, 1, fp);
	
	//Make an array to hold pointers to all packets
	packetData** allPackets = malloc(packets*sizeof(packetData*));
	
	for(int i = 0; i < packets; i++){
		allPackets[i] = parsePacket(fp);
	}
	
	for(int i = 0; i < packets; i++){
		printPacket(allPackets[i], i);
	}
}


/*
---------------------------------------------------------------------------
	Main Function
---------------------------------------------------------------------------
*/
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

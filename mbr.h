#ifndef MBR__HEADER
#define MBR__HEADER

#include <stdint.h>

struct mbr_t
{
	uint8_t bootcode[446];
	struct
	{
		uint8_t data[16];
	} __attribute__ ((packed)) part[4];
	uint16_t sig;
} __attribute__ ((packed));

int read_mbr (struct mbr_t* mbr, FILE* file);
void write_mbr (struct mbr_t* mbr, FILE* file);

#endif

#ifndef MBR__HEADER
#define MBR__HEADER

#include <stdint.h>

struct mbr_part_t
{ // we don't use partition structure
} __attribute ((packed, aligned (16)));

struct mbr_t
{
	uint8_t bootcode[446];
	struct mbr_part_t part[4];
	uint16_t sig;
} __attribute__ ((packed));

#endif

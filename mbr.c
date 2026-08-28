#include <stdio.h>
#include <stdint.h>
#include "mbr.h"

int
read_mbr (struct mbr_t* mbr, FILE* file)
{
	fseek (file, 0, 0); // MBR should be located at the very beginning
	fread ((uint8_t*) mbr, 1, sizeof (struct mbr_t) file);

	if (mbr->sig != 0xAA55)
		{
			fprintf (stderr, "read_mbr: Invalid MBR signature: %x\n", mbr->sig);
			return 0;
		}

	return 1;
}

void
write_mbr (struct mbr_t* mbr, FILE* file)
{
	fseek (file, 0, 0);
	fwrite ((const uint8_t*) mbr, 1, sizeof (struct mbr_t), file);
}

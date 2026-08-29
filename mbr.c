/* Copyright (C) 2026 sk
 *
 * This file is part of mbrperm.
 * 
 * mbrperm is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License v3 as published by the
 * Free Software Foundation.
 *
 * mbrperm is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with mbrperm. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "mbr.h"

int
read_mbr (struct mbr_t* mbr, FILE* file)
{
	if (mbr == NULL || file == NULL)
		return 0;

	fseek (file, 0, 0); // MBR should be located at the very beginning
	fread ((uint8_t*) mbr, 1, sizeof (struct mbr_t), file);

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
	if (mbr == NULL || file == NULL)
		return;

	fseek (file, 0, 0);
	fwrite ((const uint8_t*) mbr, 1, sizeof (struct mbr_t), file);
}

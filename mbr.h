/* Copyright (C) 2026 sk
 *
 * This file is part of mbrperm.
 * 
 * mbrperm is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License v3 as published by the
 * Free Software Foundation version
 *
 * mbrperm is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 */

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

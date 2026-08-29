#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mbr.h"

void
fatal (const char* msg)
{
	fprintf (stderr, "%s", msg);
	exit (EXIT_FAILURE);
	__builtin_unreachable ();
}
	
void
usage (const char* argv0)
{
	printf ("Usage: %s <file> <permutation>\n", argv0);
}

int
main (unsigned argc, char** argv)
{
	if (argc < 3)
		{	
			usage (argv[0]);
			exit (EXIT_FAILURE);
		}

	FILE* file = fopen (argv[1], "rb");

	if (file == NULL)
		{
fopen_fail:
			switch (errno)
				{
				case ENOENT:
					fatal ("main: No such file\n");
					__attribute__ ((fallthrough)); // doesn't return
				case EPERM:
					fatal ("main: Operation not permitted\n");
					__attribute__ ((fallthrough));
				default:
					fatal ("main: Could not open file for some reason\n");
				}
		}

	struct mbr_t mbr;
	
	if (!read_mbr (&mbr, file))
		{
			fclose (file);
			fatal ("main: Error reading MBR\n");
		}

	fclose (file);

	struct mbr_t permuted = mbr;

	unsigned preimage;
	unsigned image;

	char* end;

	for (unsigned i = 2; i < argc;)
		{
			preimage = strtoul (argv[i], &end, 10);

			if (end == argv[i])
				fatal ("main: Invalid permutation\n");

			i++;

			if (i >= argc)
				image = strtoul (argv[2], NULL, 10);
			else
				{
					image = strtoul (argv[i], &end, 10);

					if (end == argv[i])
						fatal ("main: Invalid permutation\n");
				}

			permuted.part[image] = mbr.part[preimage];
		}

	file = fopen (argv[1], "wb");

	if (file == NULL)
		goto fopen_fail;

	write_mbr (&permuted, file);
	fclose (file);

	return EXIT_SUCCESS;
}

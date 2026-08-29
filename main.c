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
	const char* USAGE	=
		"Usage: %s <file> <permutation>\n\n"
		"<permutation> represents the permutation to apply to <file>'s MBR "
		"partition table.\n"
		"It must be expressed in cycle notation, indexes be spaced and 0 "
		"indexed omitting parentheses and commas.\n\n"
		"The following example forms a valid input:\n"
		"%s mymbr 0 2 1\n \n"
		"This will move the first partition entry (0) to the third entry (2), "
		"the third entry to the second (1), and the second to the first.\n\n"
		"WARNING: %s currently overwrites the entirety of <file> with the "
		"modified MBR and thus %s should only be used on MBR dumps."

	printf (USAGE, argv0, argv0, argv0, argv0);
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

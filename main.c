#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "perm.h"
#include "mbr.h"

void
fatal (const char* msg, const char* argv0)
{
	fprintf (stderr, "%s: %s", argv0, msg);
	exit (EXIT_FAILURE);
	__builtin_unreachable ();
}
	
void
usage (const char* argv0)
{
	printf ("Usage: %s <file> <permutation>", argv0);
}

int
main (unsigned argc, char** argv)
{
	if (!argc)
		{	
			usage (argv[0]);
			exit (EXIT_FAILURE);
		}

	if (argc == 1) // safe to say given permutation does nothing
		exit (EXIT_SUCCESS);

	unsigned* perm = malloc (sizeof (unsigned) * argc);

	if (perm == NULL)
		fatal ("main: malloc returned NULL pointer", argv[0]);

	for (unsigned i = 0; i < argc; i++)
		perm[i] = strtoul (argv[i], NULL, "10");

	if (!valid_perm (perm, argc - 1))
		fatal ("main: Invalid permutation", argv[0]);

	FILE* file = fopen (argv[1], "rb");

	if (file == NULL)
		{
fopen_fail:
			switch (errno)
				{
				case ENOENT:
					fatal ("main: No such file", argv[0]);
					__attribute__ ((fallthrough)); // doesn't return
				case EPERM:
					fatal ("main: Operation not permitted", argv[0]);
					__attribute__ ((fallthrough));
				default:
					fatal ("main: Could not open file for some reason", argv[0]);
				}
		}

	struct mbr_t mbr;
	
	if (!read_mbr (&mbr, file))
		{
			fclose (file);
			fatal ("main: Error reading MBR", argv[0]);
		}

	fclose (file);

	struct mbr_t permuted = mbr;

	unsigned preimage;
	unsigned image;

	log_perm_size (argc - 1);

	for (unsigned* p = perm; cycle_perm (p, &left, &image, &preimage);)
		permuted.part[image] = mbr.part[preimage]; 

	file = fopen (argv[1], "ab");

	if (file == NULL)
		goto fopen_fail;

	write_mbr (&permuted, file);
	fclose (file);

	return EXIT_SUCCESS;
}

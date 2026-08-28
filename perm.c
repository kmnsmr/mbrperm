#include <stddef.h>

static unsigned perm_size;

void
log_perm_size (unsigned size)
{
	perm_size = size;
}

int
valid_perm (unsigned* perm, unsigned size)
{
	if (size > 4)
		return 0;

	unsigned occured[4] = {0};

	for (; size--; perm++)
		{
			if (*perm > 4 /* there can't be more than 4 primary partitions */
					|| occured[*perm])
				return 0;

			occured[*perm] = 1;
		}

	return 1;
}

// Returns 0 if we're finished cycling or perm is NULL, 1 else

int
cycle_perm (unsigned* perm, unsigned* preimage, unsigned* image)
{
	if (perm == NULL)
		return 0;

	static unsigned i = 0;
	static unsigned first = *perm;

	if (i >= size)
		{
			i = 0;
			return 0;
		}

	*preimage = perm[i++];

	if (i >= size)
		{
			*image = first;

			i = 0;
			return 0;
		}
	else
		*image = perm[i++];
}

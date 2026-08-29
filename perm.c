#include <stdbool.h>
#include <stddef.h>

static unsigned perm_size;

void
log_perm_size (unsigned size)
{
	perm_size = size;
}

bool
valid_perm (unsigned* perm, unsigned size)
{
	if (!size || size > 4)
		return false;

	bool occured[4] = {false};

	for (; size--; perm++)
		{
			if (!*perm || *perm > 4 || occured[*perm])
				return false;

			occured[*perm] = true;
		}

	return true;
}

/* Returns 0 if we're finished cycling or perm is NULL, 1 else.
 * Meant to be used in a for loop like in main.c
 */

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

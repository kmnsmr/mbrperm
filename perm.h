#ifndef PERM__HEADER
#define PERM__HEADER

#include <stdbool.h>

void log_perm_size (unsigned size);
bool valid_perm (unsigned* perm, unsigned size);
int cycle_perm (unsigned* perm, unsigned* preimage, unsigned* image);

#endif

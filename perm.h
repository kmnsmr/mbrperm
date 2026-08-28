#ifndef PERM__HEADER
#define PERM__HEADER

void log_perm_size (unsigned size);
int valid_perm (unsigned* perm, unsigned size);
int cycle_perm (unsigned* perm, unsigned* preimage, unsigned* image);

#endif

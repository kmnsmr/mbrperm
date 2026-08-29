CC ?= $(PREFIX)gcc
LD ?= $(PREFIX)ld

CCFLAGS :=
LDFLAGS :=

ifndef $(.DEFAULT_GOAL)

.DEFAULT_GOAL := all
$(warning No default goal, defaulting to $(.DEFAULT_GOAL))

endif

all : mbrperm

mbrperm : main.o mbr.o perm.o

	$(LD) -o $@ $? $(LDFLAGS)

%.o : %.c

	$(CC) -c $? $(CCFLAGS)

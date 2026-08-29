CC ?= $(PREFIX)gcc
CCFLAGS := -Wall -Wextra

ifeq ($(DEBUG),1)

CCFLAGS += -g -O0

endif

ifndef $(.DEFAULT_GOAL)

.DEFAULT_GOAL := all
$(warning No default goal, defaulting to $(.DEFAULT_GOAL))

endif

.PHONY : all clean

clean :

	rm mbrperm *.o

all : mbrperm

mbrperm : main.o mbr.o

	$(CC) -o $@ $^ $(CCFLAGS)

%.o : %.c

	$(CC) -c $? $(CCFLAGS)

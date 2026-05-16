##########################################################################

#############
# Toolchain #
#############

TOOLCHAIN=

CC     =$(TOOLCHAIN)gcc
LD     =$(TOOLCHAIN)ld

#########
# Flags #
#########

CFLAGS   =-Wall
LDFLAGS  =-lc

################
# Source files #
################

SRC=$(wildcard *.c articles/*.c utils/random_bool.c ../../utils/input_reader.c)

################
# Object files #
################

OBJ=$(SRC:.c=.o)

################
# Runtime file #
################

CRT=$(shell gcc --print-file-name=crt1.o)

#########################################################################

all: main.elf

#########################################################################

.PHONY: clean run

#########################################################################

## Inference rule
%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(OBJ):

main.elf: *.c articles/*.c utils/random_bool.c ../../utils/input_reader.c
	$(CC) $(CFLAGS) -o $@ $^

# Trick rule, simply to check some compiler error,
# such as : "multiple definition of '...'; previous in '...'
main.linkddebug.elf: *.o  $(CRT)
	$(LD) -o $@ $(LDFLAGS) $^

#########################################################################

run: main.elf
	./$<

clean:
	rm -rf *.elf *.o 

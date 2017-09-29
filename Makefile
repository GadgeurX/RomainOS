CC	:= i686-elf-gcc

ASM	:= nasm

RM	:= rm -rf

LDFLAGS	+= -lgcc -ffreestanding -O2 -nostdlib

CFLAGS	+= -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iincludes

CSRCS	:= $(shell find srcs -type f -name "*.c")

ASRCS	:= $(shell find srcs -type f -name "*.asm")

COBJS	:= $(CSRCS:.c=.o)

AOBJS	:= $(ASRCS:.asm=.o)

NAME	:= kernel.bin

all: $(NAME)

$(AOBJS):
	for src in $(ASRCS); do \
		$(ASM) -felf32 $$src; \
	done

$(NAME): $(COBJS) $(AOBJS)
	$(CC) -T linker.ld -o $(NAME) $(COBJS) $(AOBJS) $(LDFLAGS)

clean:
	$(RM) $(COBJS) $(AOBJS)

fclean: clean
	$(RM) $(NAME)

run:
	/mnt/c/"Program Files"/qemu/qemu-system-i386.exe -kernel kernel.bin

re: fclean all

rerun: re run

.PHONY: all re clean fclean

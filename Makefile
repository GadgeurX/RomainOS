SRCS	= src/main.c	\
	  src/io.c	\
	  src/string.c	\
	  src/fat16.c

ASM	= src/boot.asm

CC	= bcc

OBJS	= $(SRCS:.c=.o)

NAME	= kernel

$(NAME): all

all: $(OBJS)
	ld86 -d -M $(OBJS) -o $(NAME)
	nasm -f bin -o boot $(ASM)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

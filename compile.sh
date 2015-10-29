bcc -0 -ansi -c main.c
bcc -0 -ansi -c io.c
bcc -0 -ansi -c string.c
bcc -0 -ansi -c fat16.c
bcc -0 -ansi -c sh.c
ld86 -d -M main.o io.o string.o fat16.o sh.o -o kernel
nasm -f bin -o boot boot.asm
cat boot kernel /dev/zero | dd of=kernel.img bs=512 count=2880

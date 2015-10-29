bcc -0 -ansi -c main.c
bcc -0 -ansi -c io.c
bcc -0 -ansi -c string.c
bcc -0 -ansi -c fat16.c
bcc -0 -ansi -c sh.c
ld86 -d -M main.o io.o string.o fat16.o sh.o -o kernel.bin
nasm -f bin -o boot.bin boot.asm
cat boot.bin kernel.bin /dev/zero | dd of=kernel.img bs=512 count=2880

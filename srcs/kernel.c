#include 	<stdbool.h>
#include 	<stddef.h>
#include 	<stdint.h>
#include	"gdt.h"
#include	"display.h"
#include	"idt.h"
#include	"pic.h"
#include	"io.h"

struct mb_partial_info {
	unsigned long flags;
	unsigned long low_mem;
	unsigned long high_mem;
	unsigned long boot_device;
	unsigned long cmdline;
};

int main()
{
	
    terminal_initialize();
	sti;
	unsigned long* av_mem;
	av_mem = (unsigned long*)0x800000;
	terminal_writestring("Hello, kernel World!\ntest\n");
	terminal_writestring("RAM detected : ");
	terminal_putnbr(*av_mem);
	terminal_writestring("\n");
	while(1);
	return 0;
}

void kernel_main(struct mb_partial_info *mbi) {

	unsigned long* av_mem;
	av_mem = (unsigned long*)0x800000;
	*av_mem = mbi->high_mem;
	init_idt();

	init_pic();

	init_gdt();
	asm("   movw $0x18, %ax \n \
                movw %ax, %ss \n \
                movl $0x20000, %esp");

    main();
}

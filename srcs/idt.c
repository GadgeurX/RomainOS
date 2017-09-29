#include "types.h"
#include "libc.h"
#include "io.h"
#include "idt.h"

void _asm_default_int(void);
void _asm_irq_0(void);
void _asm_irq_1(void);

void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc *desc)
{
	desc->offset0_15 = (offset & 0xffff);
	desc->select = select;
	desc->type = type;
	desc->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}

void init_idt(void)
{
	int i;

	for (i = 0; i < IDTSIZE; i++) 
		init_idt_desc(0x08, (u32) _asm_default_int, INTGATE, &kidt[i]);

	init_idt_desc(0x08, (u32) _asm_irq_0, INTGATE, &kidt[32]);	// horloge
	init_idt_desc(0x08, (u32) _asm_irq_1, INTGATE, &kidt[33]);	// clavier

	kidtr.limite = IDTSIZE * 8;
	kidtr.base = IDTBASE;

	memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

	asm("lidtl (kidtr)");
}

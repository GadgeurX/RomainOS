void exec()
{
  asm "mov ax, #0x10FF";
  asm "mov ds, ax";
  asm "mov es, ax";
  asm "call #0x900:#0";
}

void load_program()
{
  //
}

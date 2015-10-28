void putc(char c)
{
  c = c;
  asm "push ax";
  asm "push bx";
  asm "mov ah, #0x0e";
  asm "mov al, 4[bp]";
  asm "mov bl, #0x0c";
  asm "int 0x10";
  asm "pop bx";
  asm "pop ax";
}

char getc()
{
  char c = 'x';
  asm "mov ah, #0";
  asm "int 0x16";
  asm "mov -5[bp], al";
  return c;
}

void puts(char * s)
{
  while(*s)
    {
      putc(*s);
      if (*s == '\n')
	putc('\r'); 
      s++;
    }
}

void gets(char *ptr)
{
  char c = 0;
  int i = 0;
  while (c != '\n' && c != '\r')
    {
      c = getc();
      putc(c);
      if (c == '\r')
	putc('\n');
      ptr[i] = c;
      i++;
    }
  ptr[i] = 0;
 }

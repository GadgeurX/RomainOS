int main()
{
  asm "mov ax, cs";
  asm "mov ds, ax";
  asm "mov es, ax";
  asm "mov ss, ax";
  asm "mov sp, #0";
  char buffer[512];
  puts("Welcome to romainOS\n");
  while (1)
    {
      puts("$>");
      gets(buffer);
      if (strcmp(buffer,"poweroff") == 0)
	break;
      if (strcmp(buffer,"test") == 0)
	putnbr(5);
      if (strcmp(buffer,"ls") == 0)
	ls_dir();
    }
}

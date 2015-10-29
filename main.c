int main()
{
  asm "mov ax, cs";
  asm "mov ds, ax";
  asm "mov es, ax";
  asm "mov ss, ax";
  asm "mov sp, #0";
  
  puts("Welcome to romainOS\n");
  return (loop());
}

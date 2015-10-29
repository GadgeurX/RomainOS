int strcmp(char* s1, char* s2)
{
  while(*s1 && (*s1 == *s2))
    {  
      s1 += 1;
      s2 += 1;
    }
  return *s1 - *s2;
}

int strncmp(char *s1, char *s2, int n)
{
  for (n = n ; n > 0; s1++, s2++, --n)
    if (*s1 != *s2)
      return ((*(char *)s1 < *(char *)s2) ? -1 : +1);
    else if (*s1 == '\0')
      return 0;
  return 0;
}

int strlen(char *s)
{
  int i = 0;
  while (s[i])
    ++i;
  return (i);
}

void revput(char *s)
{
  int l = strlen(s) - 1;
  while (l >= 0)
    putc(s[l--]);
}

int mod(int i, int j)
{
  return (i - ((i / j) * j) );
}

void putnbr(int nb)
{
  int i = 0;
  char t[12];

  if (nb < 0)
    {
      putc('-');
      nb = -nb;
    }
  while (nb)
    {
      t[i++] = mod(nb, 10) + '0';
      nb /= 10;
    }
  t[i] = 0;
  revput(t);
}

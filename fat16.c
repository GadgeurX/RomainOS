#include "FileSystem.h"

char sector[SECTOR_SIZE];

#define ptrSector(s, p) (((dentry_t *)s) + p)

void memcpy(char *src, char *dst, int size)
{
  int i = 0;

  while (i != size)
  {
    dst[i] = src[i];
    ++i;
  }
}

int end_value(int fstClus)
{
  char fat[SECTOR_SIZE];
  int byteidx = fstClus * 3 / 2;
  int a, b;
  load_sectors(fat, byteidx / SECTOR_SIZE + 1, 1);
  byteidx = mod(byteidx, SECTOR_SIZE);
  a = fat[byteidx];
  b = fat[byteidx + 1];
  if (mod(fstClus, 2) == 0)
    return ((b & 0x0f) << 8) | a;
  return (b << 4) | ((a & 0xf0) >> 4);
}

int is_root(dentry_t entry)
{
  return (entry.fstClus == 0 ? 1 : 0);
}

int cd_dir(char *dirName)
{
  /*
  int j;
  int i = (is_root(cdir) ? 19 : cdir.fstClus + 31);

  while (end_value(i) < THRESHOLD)
  {
    j = 0;
    load_sectors(sector, i, 1);
    while (j < SECTOR_SIZE / sizeof(dentry_t))
    {
      if (strcmp(ptrSector(sector, j)->name, dirName) == 0)//TODO check if empty
      {
        cdir = *ptrSector(sector, j);
        return (1);
      }
      ++j;
    }
    ++i;
  }*/
  return (0);
}

void ls_dir(dentry_t *dir)
{
  int j;
  int i = (is_root(*dir) ? 19 : dir->fstClus + 31);

  putnbr(dir->fstClus);

  while (end_value(i) < THRESHOLD)
  {
    j = 0;
    load_sectors(sector, i, 1);
    while (j < SECTOR_SIZE / sizeof(dentry_t))
    {
      puts(ptrSector(sector, j)->name);
      puts("\n");
      ++j;
    }
    ++i;
  }
}

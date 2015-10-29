#include "FileSystem.h"

char sector[SECTOR_SIZE];
dentry_t cdir = {0};

#define ptrSector(s, p) (((dentry_t *)s) + p)

void memcpy(char *src, char *dst, int size)
{
  int i = 0;

  while (i < size)
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

int is_root(dentry_t *entry)
{
  return (entry->fstClus == 0 ? 1 : 0);
}

int cd_dir(char *dirName)
{
  int j;
  int i = (is_root(cdir) ? 19 : cdir.fstClus + 31);
  char *fileName;

  while (end_value(i) < THRESHOLD)
  {
    j = 0;
    load_sectors(sector, i, 1);
    while (j < SECTOR_SIZE / sizeof(dentry_t))
    {
      /*if (get_file_name(ptrSector(sector, j));
      if (ptrSector(sector, j)->name[0] != 0 && strcmp(ptrSector(sector, j)->name, dirName) == 0)
      {
        cdir = *ptrSector(sector, j);
        return (1);
      }*/
      ++j;
    }
    ++i;
  }
  return (0);
}

void ls_dir()
{
  int j;
  int i = (is_root(&cdir) ? 19 : cdir.fstClus + 31);
  int clus = cdir.fstClus;

  //while (i < 33)
  while (end_value(clus) < THRESHOLD)//33 for the root
  {
    j = 0;
    load_sectors(sector, i, 1);
    while (j < SECTOR_SIZE / sizeof(dentry_t))
    {
      if (ptrSector(sector, j)->name[0] != 0)
      {
        puts(ptrSector(sector, j)->name);
        puts("\n");
      }
       ++j;
	  }
    clus = end_value(clus);
    ++i;
  }
}

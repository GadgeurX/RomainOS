#include "FileSystem.h"

char sector[SECTOR_SIZE];
static dentry_t cdir;
char *buffer;

#define ptrSector(s, p) (((dentry_t *)s) + p)

void initFS()
{
  cdir.fstClus = 0;
}

void memcpy(char *dst, char *src, int size)
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

int is_file(dentry_t *entry)
{
  return (entry->name[0] != 0);
}

int execute_entry(entry_func function)
{
  int j;
  int i = cdir.fstClus + 31;
  int clus = cdir.fstClus;

  if (is_root(&cdir))
    return (execute_entry_root(function));
  while (clus < THRESHOLD)
  {
    j = 0;
    load_sectors(sector, i, 1);
    for (j = 0; j < SECTOR_SIZE / sizeof(dentry_t); ++j)
    {
      function(ptrSector(sector, j));
    }
    clus = end_value(clus);
    ++i;
  }
  return (1);
}

int execute_entry_root(entry_func function)
{
  int i = 19;
  int j;
  while (i < LEN_ROOT)
  {
    load_sectors(sector, i, 1);
    for (j = 0; j < SECTOR_SIZE / sizeof(dentry_t); ++j)
    {
      function(ptrSector(sector, j));
    }
    ++i;
  }
  return (1);
}

int put_file(void *entry)
{
  if (is_file(entry))
  {
    puts(((dentry_t *)entry)->name);
    puts("\n");
  }
}

int enter_file(void *entry)
{
  if (is_file(entry))
  {
    if (strlen(buffer) > 0 && strncmp(((dentry_t *)entry)->name, buffer, strlen(buffer)) == 0)
      cdir = *((dentry_t *)entry);
  }
}

int cd_dir(char *dirName)
{
  buffer = dirName;
  execute_entry(enter_file);
  return (1);
}

int ls_dir()
{
  execute_entry(put_file);
  return (1);
}

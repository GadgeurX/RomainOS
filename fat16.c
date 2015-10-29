#define THRESHOLD 0xff8
#define SECTOR_SIZE 512

#pragma pack(1)
typedef struct {
  char name[0xB];
  char attr;
  char resv[10];
  int wrtTime;
  int wrtDate;
  int fstClus;
  int filesize[2];
}       dentry_t;
#pragma pack()

char sector[SECTOR_SIZE];

void memcpy(char *src, char *dst, int size)
{
  int i = 0;

  while (i != size)
    {
      dst[i] = src[i];
      i++;
    }
}

void ls_dir()
{
  int i = 19;
  int j;  

  while (i < 33)
    {
      load_sectors(sector, i, 1);
      j = 0;
      while (j < SECTOR_SIZE / sizeof(dentry_t))
	{
	  if (strlen((((dentry_t *)sector) + j)->name) > 3)
	    {
	      puts((((dentry_t *)sector) + j)->name);
	      puts("\n");
	    }	
	  j++;
	}
      i++;
    }
}

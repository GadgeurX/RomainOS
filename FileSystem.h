#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#define THRESHOLD 0xff8
#define SECTOR_SIZE 512
#define FILENAME_SIZE 0xB

#pragma pack(1)
typedef struct {
  char name[FILENAME_SIZE];
  char attr;
  char resv[10];
  int wrtTime;
  int wrtDate;
  int fstClus;
  int filesize[2];
}       dentry_t;
#pragma pack()

#endif

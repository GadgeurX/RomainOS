#include "FileSystem.h"

typedef int (*func)(void *);

char *g_commands[] = {
  "ls",
  "poweroff",
  "cd",
  (void *)0
};

dentry_t *get_entry()
{
  static dentry_t cdir = {0};
  return (&cdir);
}

int ls(void *nan)
{
  (void)nan;
  ls_dir(get_entry());
  return (1);
}

int poweroff(void *nan)
{
  (void)nan;
  return (0);
}

int cd(void *path)
{
  cd_dir((char *)path);
  return (1);
}


int find_command(char *cmd)
{
  int i = 0;

  while (g_commands[i])//PROUT
  {
    if (strcmp(cmd, g_commands[i]) == 0)
      return (i);
    ++i;
  }
  return (-1);
}

int handle_commandline(char *s)
{
  int index;
  func cmd[3];

  cmd[0] = ls;
  cmd[1] = poweroff;
  cmd[2] = cd;
  if ((index = find_command(s)) >= 0)
    return (cmd[index]("DIR"));
  return (2);
}

/* Main entry point ! */
int loop()
{
  int val;
  char buffer[512];

  while (1)
  {
    puts("$>");
    gets(buffer);
    if ((val = handle_commandline(buffer)) == 0)
      break;
    if (val == 2)
      puts("Command not found\n");
  }
  return (0);
}

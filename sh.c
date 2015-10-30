#include "FileSystem.h"

typedef int (*func)(void *);

char *g_commands[] = {
  "ls",
  "poweroff",
  "cd",
  (void *)0
};

int ls(void *nan)
{
  (void)nan;
  ls_dir();
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
    if (strncmp(cmd, g_commands[i], strlen(g_commands[i])) == 0)
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
    return (cmd[index](s + 3));
  return (2);
}

/* Main entry point ! */
int loop()
{
  int val;
  char buffer[512];
  initFS();
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

typedef int (*func)();

char *g_commands[] = {
  "ls",
  "poweroff",
  (void *)0
};

int ls()
{
  ls_dir();
  return (1);
}

int poweroff()
{
  return (0);
}

int find_command(char *cmd)
{
  int i = 0;

  while (g_commands[i])
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
  cmd[2] = (void *)0;
  if ((index = find_command(s)) >= 0)
    return (cmd[index]());
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

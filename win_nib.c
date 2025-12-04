#define NIB_IMPLEMENTATION
#define ANSI_ENABLE
#include "nib.h"

int main(void)
{
  CMD cmd = { 0 };

  nib_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", "-o", "main.exe", "main.c");
  if(!nib_cmd_run(cmd)) return 1;
  return 0;
}

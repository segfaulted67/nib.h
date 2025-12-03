#include <stdio.h>
#define NIB_IMPLEMENTATION
#define ANSI_ENABLE
#include "nib.h"

int main(void)
{
  CMD cmd = { 0 };
  CMD cmd1 = { 0 };
  nib_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "--std=c11", "-o", "main", "main.c", "-lraylib", "-lGL");
  nib_cmd_run(cmd1);
  return 0;
}

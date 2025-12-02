#include <stdio.h>
#define NIB_IMPLEMENTATION
#include "nib.h"

int main(void)
{
  nib_Cmd cmd = { 0 };
  nib_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "--std=c11", "-o", "main", "main.c");
  nib_cmd_run(cmd);
  return 0;
}

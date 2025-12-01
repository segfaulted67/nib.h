#include <stdio.h>
#define NIB_H_IMPLEMENTATION
#include "nib.h"

int main(void)
{
  nib_Cmd cmd = { 0 };
  nib_cmd_append(&cmd, "cc", "-o", "main", "main.c");
  for(size_t i = 0; i < cmd.count; i++)
  {
    nib_Info("%s", cmd.items[i]);
  }
  nib_cmd_run(cmd);
  return 0;
}

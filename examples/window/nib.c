#define NIB_IMPLEMENTATION
#include "../../nib.h"

int main(void)
{
  CMD cmd = { 0 };
  nib_cmd_append(&cmd, "cc", "-o", "main", "main.c", "-lraylib");
  if(!nib_cmd_run(cmd))   return 1;
  return 0;
}

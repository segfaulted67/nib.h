#include <stdio.h>
#define NIB_IMPLEMENTATION
#include "nib.h"

int main(void)
{
  CMD cmd = { 0 };
  SB sb = { 0 };
  nib_sb_append_cstr(&sb, "Hello");
  nib_sb_append_cstr(&sb, "World");
  nib_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", "--std=c11", "-o", "main", "main.c", "-lraylib", "-lGL");
  if(!nib_cmd_run(cmd)) return 1;
  printf("%s", nib_sb_peek(sb));
  nib_sb_free(sb);
  return 0;
}

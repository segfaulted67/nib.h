#ifndef NIB_H
#define NIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define NIB_C_RESET   "\033[0m"
#define NIB_C_RED     "\033[31m"
#define NIB_C_GREEN   "\033[32m"
#define NIB_C_YELLOW  "\033[33m"
#define NIB_C_BLUE    "\033[34m"
#define NIB_C_MAGENTA "\033[35m"
#define NIB_C_CYAN    "\033[36m"
#define NIB_C_WHITE   "\033[37m"
#define NIB_C_BOLD    "\033[1m"
#define NIB_C_BRED    "\033[91m"
#define NIB_C_BYELLOW "\033[93m"
#define NIB_C_BBLUE   "\033[94m"

#define nib_Log(stream, color, level, fmt, ...)  fprintf(stream, color "[" level "] " fmt "\n", ##__VA_ARGS__)
#define nib_Error(fmt, ...) nib_Log(stderr, NIB_C_RED, "Error", NIB_C_RESET "%s:%d (%s()): " fmt, ##__VA_ARGS__)
#define nib_Info(fmt, ...)  nib_Log(stdout, NIB_C_BLUE, "Info", NIB_C_RESET fmt, ##__VA_ARGS__)

#define NIB_ForEach(type, it, da) for (type *it = (da)->items; it < (da)->items + (da)->capacity; ++it)

typedef struct{
  const char **items;
  size_t count;
  size_t capacity;
} nib_Cmd;

typedef struct{
  char *items;
  size_t count;
  size_t capacity;
} StringBuilder;

#endif // NIB_H

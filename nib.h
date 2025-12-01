#ifndef NIB_H
#define NIB_H

// TODO: Fix segfaulted issue
#ifdef NIB_H_IMPLEMENTATION
#if defined(__cplusplus)
extern "C" {
#endif

// ------------------------------------------------------------------------------------------------------------------
// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif
// ------------------------------------------------------------------------------------------------------------------
// Constants
#define DA_INITIAL_CAP 256
// ------------------------------------------------------------------------------------------------------------------
// Colors
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

// ------------------------------------------------------------------------------------------------------------------
// Logging
#define nib_Log(stream, color, level, fmt, ...)  fprintf(stream, color "[" level "] " fmt "\n", ##__VA_ARGS__)
#define nib_Error(fmt, ...) nib_Log(stderr, NIB_C_RED, "Error", NIB_C_RESET "%s:%d (%s()): " fmt, ##__VA_ARGS__)
#define nib_Info(fmt, ...)  nib_Log(stdout, NIB_C_BLUE, "Info", NIB_C_RESET fmt, ##__VA_ARGS__)
#define NIB_ASSERT(x)   assert(x)

// Foreach loop
#define nib_foreach(type, it, da) for (type *it = (da)->items; it < (da)->items + (da)->capacity; ++it)

#ifdef __cplusplus
#define NIB_DECTYPE_CAST(T) (decltype(T))
#else
#define NIB_DECTYPE_CAST(T)
#endif

// typecasting useful C functions
#define NIB_MALLOC(x)         malloc(x)
#define NIB_REALLOC(x, size)  realloc(x, size)
#define NIB_FREE(x)           free(x)
// ------------------------------------------------------------------------------------------------------------------
// Structures
typedef struct{
  const char **items;
  size_t count;
  size_t capacity;
} nib_Cmd;

typedef struct{
  char *items;
  size_t count;
  size_t capacity;
} nib_StringBuilder;

#ifdef _WIN32
typedef HANDEL Pid;
#else
typedef int Pid;
#endif
// ------------------------------------------------------------------------------------------------------------------
// Functions
#define nib_da_reserve(da, expected_capacity)                                     \
  do {                                                                            \
    if(expected_capacity > (da)->capacity)                                        \
    {                                                                             \
      if((da)->capacity == 0) {                                                   \
        (da)->capacity = DA_INITIAL_CAP;                                          \
      }                                                                           \
      while(expected_capacity > (da)->capacity) {                                 \
        (da)->capacity *= 2;                                                      \
      }                                                                           \
      (da)->items = NIB_DECTYPE_CAST((da)->items)NIB_REALLOC((da)->items, (da)->capacity * sizeof((da)->items));      \
      NIB_ASSERT((da)->items != NULL && "Bro dont have enough RAM in BIG 25 lol");  \
    }                                                                             \
  } while (0)

#define nib_da_append(da, item)                                                           \
  do {                                                                                    \
    if((da)->count >= (da)->capacity)                                                     \
    {                                                                                     \
      (da)->capacity = (da)->capacity == 0 ? DA_INITIAL_CAP : (da)->capacity * 2;         \
      (da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items));          \
      assert((da)->items != NULL && "Buy more RAM LOL!!");                                \
    }                                                                                     \
    (da)->items[(da)->count++] = (item);                                                  \
  } while (0)

#define nib_da_append_many(da, new_items, new_items_count)                      \
  do {                                                                          \
    nib_da_reserve((da), (da)->count + new_items_count);                        \
    memcpy((da)->items + (da)->count, (new_items), (new_items_count)*sizeof(*(da)->items));       \
    (da)->count += (new_items_count);                                           \
  } while (0)

#define nib_da_free(da) NIB_FREE((da).items)

void nib_cmd_append_null(nib_Cmd *cmd, ...)
{
  va_list args;
  va_start(args, cmd);

  const char *arg = va_arg(args, const char *);
  while(arg != NULL)
  {
    nib_da_append(cmd, arg);
    arg = va_arg(args, const char *);
  }
  va_end(args);
}

#define nib_cmd_append(cmd, ...)  \
  nib_cmd_append_null(cmd, __VA_ARGS__, NULL)


Pid nib_cmd_run(nib_Cmd cmd)
{
  Pid cpid = fork();

  nib_Cmd cmd_null = { 0 };
  nib_da_append_many(&cmd_null, cmd.items, cmd.count);
  nib_cmd_append(&cmd_null, NULL);

  if(cpid == 0)
  {
    if(execvp(cmd.items[0], (char * const*)cmd_null.items) < 0) {
      nib_Error("Could not exec child process for %s: %s", cmd.items[0], strerror(errno));
      exit(1);
    }
  }
  else
  {
    nib_Error("Could not exec child process for %s: %s", cmd.items[0], strerror(errno));
  }
  return cpid;
}

#endif



// Backword Compatibility
#define CMD nib_Cmd
#define NIB_CMD nib_Cmd
// ------------------------------------------------------------------------------------------------------------------
#if defined(__cplusplus)
}
#endif

#endif // NIB_H

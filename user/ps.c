// PS-like utility for XV6 that helps debugging buddy-allocator
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char **argv)
{
  int proc = fork();
  if (proc > 0) {
    //buddy_debug_set(1);
  } else {
    if (proc == 0) {
      procdump();
      printf("Exiting child process...\n");
    } else {
      exit(-2);
    }
  }
  exit(0);
}
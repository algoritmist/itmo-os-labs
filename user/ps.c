// PS-like utility for XV6 that helps debugging buddy-allocator
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char **argv)
{
  procdump();
  exit(0);
}
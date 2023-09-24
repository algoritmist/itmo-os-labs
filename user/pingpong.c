#include "kernel/types.h"
#include "user/user.h"

#define PING "PING"
#define PONG "PONG"

int close_read(int p[]) { return close(p[0]); }

int close_write(int p[]) { return close(p[1]); }

int pipe_read(int p[], char *buf, int size) { return read(p[0], buf, size); }

int pipe_write(int p[], char *buf, int size) { return write(p[1], buf, size); }

void pipe_close(int p[])
{
  close_read(p);
  close_write(p);
}

int main(int argc, char *argv[])
{
  int f[2], s[2];
  if (pipe(f) == -1) {
    fprintf(2, "Error creating pipe...");
    exit(-1);
  }
  if (pipe(s) == -1) {
    fprintf(2, "Error creating pipe...");
    exit(-1);
  }

  dump();

  int pr = fork();
  int pid = getpid();

  if (pr > 0) {
    close_read(f);
    pipe_write(f, PING, sizeof(PING));
    close_write(f);
    close_write(s);
    char buf[sizeof(PONG)];
    pipe_read(s, buf, sizeof(buf));
    close_read(s);
    printf("%d: got %s\n", pid, buf);
  } else {
    if (pr == 0) {
      close_write(f);
      char buf[sizeof(PING)];
      pipe_read(f, buf, sizeof(buf));
      close_read(f);
      printf("%d: got %s\n", pid, buf);
      close_read(s);
      pipe_write(s, PONG, sizeof(PONG));
      close_write(s);
    } else {
      fprintf(2, "Error creating fork...");
      pipe_close(s);
      pipe_close(f);
      exit(-1);
    }
  }

  exit(0);
}
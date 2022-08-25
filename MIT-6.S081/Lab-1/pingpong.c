#include "kernel/types.h"
#include "user/user.h"

int main() {
  int p[2];
  char buf[100];
  int n;
  pipe(p);
  if (fork() == 0) {
    char *argv[] = {"<pid>:", "recieved", "ping"};
    close(p[0]);
    write(p[1], '1', 1);
    close(p[1]);
    exec("echo", argv);
  } else {
    char *argv[] = {"<pid>:", "recieved", "pong"};
    close(p[1]);
    n = read(p[0], buf, 1) if (n < 0) {}
    exec("echo", argv);
  }
  exit(0);
}
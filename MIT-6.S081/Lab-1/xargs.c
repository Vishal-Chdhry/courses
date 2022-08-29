#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char buff[512] = {0};
  read(0, buff, 512);

  int pid, status;
  char *argvs[MAXARG] = {0};

  int idx = 0;
  for (int i = 1; i < argc; i++) {
    argvs[idx++] = argv[i];
  }
  argvs[idx++] = buff;

  for (int i = 1; i < idx; i++) {
    pid = fork();
    if (pid == 0) {
      char *newArgs[] = {argvs[0], argvs[i], 0};
      exec(argvs[0], newArgs);
      printf("exec failed!\n");
      exit(1);
    } else {
      wait(&status);
    }
  }

  exit(0);
}

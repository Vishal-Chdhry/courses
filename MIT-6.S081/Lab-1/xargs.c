#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char buff[512] = {0};
  read(0, buff, 512);

  char *argvs[MAXARG] = {0};

  int idx = 0;
  for (int i = 1; i < argc; i++) {
    argvs[idx++] = argv[i];
  }
  argvs[idx] = buff;
  exec(argvs[0], argvs);
  printf("exec failed!\n");
  exit(1);
}

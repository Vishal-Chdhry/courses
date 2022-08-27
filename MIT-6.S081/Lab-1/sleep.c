#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    sleep(argv[1]);
  }
  exit(0);
#include "kernel/types.h"
#include "user/user.h"

  int a2i(const char *s) {
    int sign = 1;
    if (*s == '-') {
      sign = -1;
      s++;
    }
    int num = 0;
    while (*s) {
      num = ((*s) - '0') + num * 10;
      s++;
    }
    return num * sign;
  }

  int main(int argc, char *argv[]) {
    if (argc > 1) {
      sleep(a2i(argv[1]));
    }
    exit(0);
  }
}
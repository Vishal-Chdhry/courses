#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

char *fmtname(char *path) {
  static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ) return p;
  memmove(buf, p, strlen(p));
  memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
  return buf;
}

void find(char *path, char *file) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0) {
    return;
  }

  if (fstat(fd, &st) < 0) {
    close(fd);
    return;
  }

  switch (st.type) {
    case T_DEVICE:
    case T_FILE:
      if (strcmp(fmtname(path), fmtname(file)) == 0) {
        printf("%s %d %d %l\n", path, st.type, st.ino, st.size);
      }
      break;

    case T_DIR:
      if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
        break;
      }
      strcpy(buf, path);
      p = buf + strlen(buf);
      *p++ = '/';
      if (strcmp(fmtname(path), fmtname(file)) == 0) {
        printf("%s %d %d %l\n", path, st.type, st.ino, st.size);
      }

      while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0) continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
          continue;
        }
        find(buf, file);
      }
      break;
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  int i;

  if (argc < 3) {
    exit(0);
  }
  find(argv[1], argv[2]);
  exit(0);
}

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

int main(int argc, char* argv[]) {
  int srcFd = open("./src.txt", O_RDONLY);
  if (srcFd == -1) {
    error_and_exit();
  }

  int dstFd = open("./dst.txt", O_WRONLY | O_CREAT);
  if (dstFd == -1) {
    error_and_exit();
  }

  char buffer[16];
  while (1) {
    int num = read(srcFd, buffer, 16);
    if (num == 0) {
      break;
    }
    write(dstFd, buffer, num);
  }
  close(srcFd);
  close(dstFd);
  return 0;
}

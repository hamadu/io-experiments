#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int fd = open("./read.cc", O_RDONLY);
  if (fd == -1) {
    printf("open error(%d): %s\n", errno, strerror(errno));
    return 1;
  }

  char buf[120];
  read(fd, buf, 100);

  printf("opened fd = %d\n", fd);
  printf("== first 100 bytes ==\n%s\n", buf);

  read(fd, buf, 100);
  printf("== next 100 bytes ==\n%s\n", buf);

  close(fd);

  return 0;
}

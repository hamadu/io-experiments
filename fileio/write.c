#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int fd = open("./test.txt", O_WRONLY | O_CREAT);
  if (fd == -1) {
    printf("open error(%d): %s\n", errno, strerror(errno));
    return 1;
  }

  const char* fizz = "fizz";
  const char* buzz = "buzz";
  char num[10];
  for (int i = 1 ; i <= 5000000 ; i++) {
    int flg = 0;
    if (i % 3 == 0) {
      flg = 1;
      write(fd, fizz, strlen(fizz));
    }
    if (i % 5 == 0) {
      flg = 1;
      write(fd, buzz, strlen(buzz));
    }
    if (flg == 0) {
      sprintf(num, "%d", i);
      write(fd, num, strlen(num));
    }
    write(fd, "\n", 1);
  }
  close(fd);
  return 0;
}

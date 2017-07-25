#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  int fd = open("fifo", O_RDONLY);
  char buf[6];
  while (1) {
    int num = read(fd, buf, 5);
    if (num == 0) {
      break;
    }
    printf("%s\n", buf);
  }
  return 0;
}

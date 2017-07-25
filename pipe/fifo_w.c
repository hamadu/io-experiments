#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  int fd = open("fifo", O_WRONLY);
  char data[3] = {'c', 'a', 't'};
  for (int i = 0 ; i < 100 ; i++) {
    write(fd, data, 3);
  }
  return 0;
}

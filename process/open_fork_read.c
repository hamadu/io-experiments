#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

int main(int argc, char* argv[]) {
  int fd = open("./src.txt", O_RDONLY);
  if (fd == -1) {
    print_error_and_exit();
  }

  pid_t result = fork();
  if (result == -1) {
    print_error_and_exit();
  }

  if (result == 0) {
    char buf[6];
    read(fd, buf, 6);
    printf("hi. this is child process : %s\n", buf);
  } else {
    sleep(3);
    char buf[6];
    read(fd, buf, 6);
    printf("hi. this is parent process : %s\n", buf);
  }
  return 0;
}

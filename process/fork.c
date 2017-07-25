#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

static int global_num = 100;

int main(int argc, char* argv[]) {
  int num = 42;
  pid_t result = fork();
  if (result == -1) {
    print_error_and_exit();
  }

  if (result == 0) {
    num += 10;
    global_num++;
    printf("hi. this is child process : %d, %d\n", num, global_num);
  } else {
    sleep(3);
    num += 4;
    global_num += 2;
    printf("hi. this is parent process : %d, %d\n", num, global_num);
  }
  return 0;
}

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

int main(int argc, char* argv[]) {
  int status;
  pid_t result = fork();
  if (result == -1) {
    print_error_and_exit();
  }

  if (result == 0) {
    printf("hi. this is child process\n");
  } else {
    waitpid(result, &status, 0);
    printf("hi. this is parent process\n");
  }
  return 0;
}

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  int pipefd[2];
  pipe(pipefd);

  int readFd = pipefd[0];
  int writeFd = pipefd[1];

  pid_t result = fork();
  if (result == 0) {
    char data[100];
    for (int i = 0 ; i < 100 ; i++) {
      data[i] = (char)('a' + (i % 26));
    }
    write(writeFd, data, 100);
  } else {
    char buf[5];
    while (1) {
      int num = read(readFd, buf, 5);
      if (num == 0) {
        break;
      }
      printf("%s\n", buf);
    }
  }
  return 0;
}

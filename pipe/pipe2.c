#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  int pipefd[2];
  pipe(pipefd);

  int readFd = pipefd[0];
  int writeFd = pipefd[1];

  pid_t result = fork();
  if (result == 0) {
    close(readFd);
    dup2(writeFd, STDOUT_FILENO);
    execl("/bin/ls", "al", (char *)NULL);
  } else {
    close(writeFd);
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

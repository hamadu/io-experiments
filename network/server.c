#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

int main(int argc, char* argv[]) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    print_error_and_exit();
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_aton("127.0.0.1", &addr.sin_addr);
  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    print_error_and_exit();
  }

  if (listen(fd, 100) < 0) {
    print_error_and_exit();
  }

  while (1) {
    int peerFd = accept(fd, NULL, NULL);
    char *data = "boom";
    write(peerFd, data, strlen(data));
    close(peerFd);
  }

  return 0;
}

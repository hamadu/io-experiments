#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

int main(int argc, char* argv[]) {
  struct sockaddr_un sock;
  sock.sun_family = AF_UNIX;
  strcpy(sock.sun_path, "foo.sock");
  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  int size = offsetof(struct sockaddr_un, sun_path) + strlen(sock.sun_path);
  if (bind(fd, (struct sockaddr *)&sock, size) < 0) {
    print_error_and_exit();
  }
  printf("socket bound\n");
  return 0;
}

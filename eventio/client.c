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

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_aton("127.0.0.1", &addr.sin_addr);


  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    print_error_and_exit();
  }

  while (true) {
    int n;
    scanf("%d", &n);

    char *data = "boom";
    write(fd, data, strlen(data));

    char[] buffer;
    read(fd, buf, 120);
    printf("== response from server ==\n%s\n", buf);
  }
  return 0;
}

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    return milliseconds;
}

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("usage: %s [address]\n", argv[0]);
    exit(1);
  }

  int fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_aton(argv[1], &addr.sin_addr);

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    print_error_and_exit();
  }

  for (int cur = 0 ; cur < 100 ; cur++) {
    long long cur = current_timestamp();

    char *data = "boom";
    write(fd, data, strlen(data));

    char buf[120];
    read(fd, buf, 120);

    long long elapsed = current_timestamp() - cur;
    printf("wait = %lld\n", elapsed);
  }

  close(fd);
  return 0;
}

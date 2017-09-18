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
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_aton("127.0.0.1", &addr.sin_addr);

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    print_error_and_exit();
  }

  long long max_wait = 0;

  for (int cur = 0 ; cur < 1000 ; cur++) {
    long long cur = current_timestamp();

    char *data = "boom";
    write(fd, data, strlen(data));

    char buf[120];
    read(fd, buf, 120);

    long long elapsed = current_timestamp() - cur;
    if (max_wait < elapsed) {
      max_wait = elapsed;
    }
  }
  printf("max_wait = %lld\n", max_wait);

  close(fd);
  return 0;
}

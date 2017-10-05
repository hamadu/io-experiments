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
#include <pthread.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

void* connect_and_boom(void *arg) {
  int wait = 10;
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  char* host =  (char*) arg;
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_aton(host, &addr.sin_addr);

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    print_error_and_exit();
  }

  while (1) {
    char *data = "boom";
    write(fd, data, strlen(data));

    char buf[120];
    read(fd, buf, 120);
    usleep(wait * 1000);
  }

  close(fd);

  return NULL;
}

int main(int argc, char* argv[]) {
  if (argc <= 2) {
    printf("usage: %s [address] [wait] [concurrency]\n", argv[0]);
    exit(1);
  }

  int wait = atoi(argv[2]);
  int concurrency = atoi(argv[3]);
  for (int i = 0 ; i < concurrency ; i++) {
    pthread_t thread;
    pthread_create(&thread, NULL, *connect_and_boom, argv[1]);
  }

  while (1) {
    sleep(1);
  }

  return 0;
}

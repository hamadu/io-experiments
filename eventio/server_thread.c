#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define MAX_EVENTS 100

void print_error_and_exit(const char* s) {
  perror(s);
  exit(1);
}

void* process_client(void *arg) {
  int peerFd = *(int *)arg;

  char buf[127];
  while (1) {
    int read_result = read(peerFd, buf, 127);
    if (read_result <= 0) {
      return NULL;
    }

    int write_result = write(peerFd, buf, read_result);
    if (write_result == -1) {
      return NULL;
    }
  }
}


int main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("usage: %s [address]\n", argv[0]);
    exit(1);
  }

  signal(SIGPIPE, SIG_IGN);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    print_error_and_exit("create socket");
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_aton(argv[1], &addr.sin_addr);
  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    print_error_and_exit("bind address to the socket");
  }

  if (listen(sockfd, 10000) < 0) {
    print_error_and_exit("listen to the socket");
  }

  while (1) {
    int peerfd = accept(sockfd, NULL, NULL);
    pthread_t thread;
    pthread_create(&thread, NULL, *process_client, &peerfd);
  }
}

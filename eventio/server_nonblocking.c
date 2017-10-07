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
#include <fcntl.h>

#define MAX_CLIENTS 10000

void print_error_and_exit(const char* s) {
  perror(s);
  exit(1);
}

int fds[MAX_CLIENTS];

void make_non_blocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    print_error_and_exit("F_GETFL");
  }
  int result = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (result == -1) {
    print_error_and_exit("F_SETFL");
  }
}

int add_client(int peerFd) {
  for (int i = 0 ; i < MAX_CLIENTS ; i++) {
    if (fds[i] == -1) {
      fds[i] = peerFd;
      return 1;
    }
  }
  return 0;
}

int close_client(int peerFd) {
  for (int i = 0 ; i < MAX_CLIENTS ; i++) {
    if (fds[i] == peerFd) {
      fds[i] = -1;
      close(peerFd);
      return 1;
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("usage: %s [address]\n", argv[0]);
    exit(1);
  }

  signal(SIGPIPE, SIG_IGN);

  memset(fds, -1, sizeof(fds));

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  make_non_blocking(sockfd);
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

  if (listen(sockfd, MAX_CLIENTS) < 0) {
    print_error_and_exit("listen to the socket");
  }

  char buf[127];

  while (1) {
    int result = accept(sockfd, NULL, NULL);
    if (result >= 1) {
      int peerFd = result;
      if (!add_client(peerFd)) {
        // cannot handle client anymore
        close(peerFd);
      }
    }
    usleep(1000);

    for (int i = 0 ; i < MAX_CLIENTS ; i++) {
      if (fds[i] != -1) {
        int peerFd = fds[i];
        int read_result = read(peerFd, buf, 127);
        if (read_result == -1) {
          if (errno == EWOULDBLOCK) {
            continue;
          }
          close_client(peerFd);
        } else if (read_result == 0) {
          close_client(peerFd);
        } else {
          int write_result = write(peerFd, buf, read_result);
          if (write_result == -1 && errno != EWOULDBLOCK) {
            close_client(peerFd);
          }
        }
      }
    }
  }
}

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>

#define MAX_EVENTS 100

void print_error_and_exit(const char* s) {
  perror(s);
  exit(1);
}

int main(int argc, char** argv) {
  signal(SIGPIPE, SIG_IGN);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    print_error_and_exit("create socket");
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_aton("127.0.0.1", &addr.sin_addr);
  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    print_error_and_exit("bind address to the socket");
  }

  if (listen(sockfd, 10000) < 0) {
    print_error_and_exit("listen to the socket");
  }

  int epollfd = epoll_create1(0);

  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = sockfd;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
    print_error_and_exit("registering the socket descriptor to epoll");
  }

  struct epoll_event events[MAX_EVENTS];
  while (1) {
    int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
      print_error_and_exit("waiting events");
    }

    for (int i = 0 ; i < nfds ; i++) {
      int fd = events[i].data.fd;
      if (fd == sockfd) {
        int peerfd = accept(fd, NULL, NULL);
        struct epoll_event cev;
        cev.events = EPOLLIN | EPOLLET;
        cev.data.fd = peerfd;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, peerfd, &cev) == -1) {
          print_error_and_exit("registering the peer socket descriptor to epoll");
        }
      } else {
        char *data = "boom";
        int write_result = write(fd, data, strlen(data));
        if (write_result == EPIPE) {
          if (epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL) == -1) {
            print_error_and_exit("closing peer socket descriptor to epoll");
          }
        }
      }
    }
  }
}

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>

void* another(void *arg) {
  int fd = open("./src.txt", O_RDONLY);
  char buf[6];
  read(fd, buf, 6);

  printf("hello from another thread: %d, %s\n", fd, buf);
}

int main(int argc, char* argv[]) {

  pthread_t thread;
  pthread_create(&thread, NULL, *another, NULL);

  sleep(3);

  int fd = open("./src.txt", O_RDONLY);
  char buf[6];
  read(fd, buf, 6);

  printf("hello from main thread : %d, %s\n", fd, buf);

  return 0;
}

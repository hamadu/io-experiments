#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>

int fd;

void* another(void *arg) {
  char buf[6];
  read(fd, buf, 6);
  printf("hello from another thread: %s\n", buf);
}

int main(int argc, char* argv[]) {
  fd = open("./src.txt", O_RDONLY);

  pthread_t thread;
  pthread_create(&thread, NULL, *another, NULL);

  char buf[6];
  read(fd, buf, 6);

  printf("hello from main thread : %s\n", buf);

  return 0;
}

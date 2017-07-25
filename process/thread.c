#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int global_num = 100;

void* another(void *arg) {
  global_num = 200;
  printf("hello from another thread: %d\n", global_num);
  global_num = 300;
}

int main(int argc, char* argv[]) {
  pthread_t thread;
  pthread_create(&thread, NULL, *another, NULL);

  sleep(3);

  printf("hello from main thread: %d\n", global_num);

  return 0;
}

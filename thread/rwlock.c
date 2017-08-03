#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int x;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int read_x() {
  pthread_rwlock_rdlock(&rwlock);
  int y = x;
  pthread_rwlock_unlock(&rwlock);
  return y;
}

void write_x(int a) {
  pthread_rwlock_wrlock(&rwlock);
  x += a;
  pthread_rwlock_unlock(&rwlock);
}

void* doit(void *arg) {
  return NULL;
}

int main(int argc, char* argv[]) {
  for (int cur = 0 ; cur < 100 ; cur++) {
    pthread_t thread;
    pthread_create(&thread, NULL, *doit, NULL);
  }
  sleep(3);
  printf("total: %d\n", x);
  return 0;
}

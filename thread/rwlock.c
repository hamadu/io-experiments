#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a[4];
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int read_x(int idx) {
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

void* do_read(void *arg) {
  return NULL;
}

void* do_write(void *arg) {
  return NULL;
}

int main(int argc, char* argv[]) {
  memset(a, 0, sizeof(a));

  for (int cur = 0 ; cur < 4 ; cur++) {
    pthread_t thread;
    pthread_create(&thread, NULL, *do_read, (void *)1);
    pthread_create(&thread, NULL, *do_write, (void *)1);
  }
  sleep(3);
  return 0;
}

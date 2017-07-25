#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
  mkfifo("fifo", S_IRWXU);
  while (1) {
    sleep(1);
  }
  return 0;
}

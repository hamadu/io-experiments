#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_error_and_exit() {
  printf("error(%d): %s\n", errno, strerror(errno));
  exit(1);
}

int main(int argc, char* argv[]) {
  FILE *src = fopen("./src.txt", "r");
  if (src == NULL) {
    print_error_and_exit();
  }

  FILE *dst = fopen("./dst.txt", "w");
  if (dst == NULL) {
    print_error_and_exit();
  }

  while (1) {
    int ch = fgetc(src);
    if (ch == EOF) {
      break;
    }
    fputc(ch, dst);
  }
  fclose(src);
  fclose(dst);
  return 0;
}

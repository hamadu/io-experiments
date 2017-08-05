#include <unistd.h>
#include <stdio.h>

int swapcase(int ch) {
  if ('a' <= ch && ch <= 'z') {
    return 'A' + (ch - 'a');
  } else if ('A' <= ch && ch <= 'Z') {
    return 'a' + (ch - 'A');
  } else {
    return ch;
  }
}

int main(int argc, char* argv[]) {
  FILE *reader = popen("/bin/ls -al", "r");
  while (1) {
    int ch = fgetc(reader);
    if (ch == EOF) {
      break;
    }
    fputc(swapcase(ch), stdout);
  }
  pclose(reader);
  return 0;
}

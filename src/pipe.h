#ifndef CODEC2_PIPE_H
#define CODEC2_PIPE_H

#if defined(_MSC_VER)
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#endif

void init_binary_stdin_stdout() {
#if defined(_MSC_VER)
  int result = _setmode(_fileno(stdin), _O_BINARY);
  if (-1 == result) {
    fprintf(stderr, "cannot set binary mode to stdin\n");
    exit(1);
  }
  result = _setmode(_fileno(stdout), _O_BINARY);
  if (-1 == result) {
    fprintf(stderr, "cannot set binary mode to stdout\n");
    exit(1);
  }
#endif
}

#endif  // CODEC2_PIPE_H

/*
   tquisk_filter.c

   Unit test for complex band pass filters in src/filter.c

   cd codec2/build_linux
   ./misc/mksine - 1500 2 | unittest/tquisk_filter | aplay

   By adjusting the frequency you can audibly test filter response.
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "filter.h"
#include "comp_prim.h"
#include "filter_coef.h"

#define N 159 /* processing buffer size  (odd number deliberate) */
#define CENTRE 1500.0
#define FS 8000.0

int main() {
  short buf_short[N];
  COMP buf[N];
  struct quisk_cfFilter *bpf;
  int i;

  bpf = malloc(sizeof(struct quisk_cfFilter));
  assert(bpf != NULL);
  quisk_filt_cfInit(bpf, filtP200S400, sizeof(filtP200S400) / sizeof(float));
  quisk_cfTune(bpf, CENTRE / FS);

  while (fread(buf_short, sizeof(short), N, stdin) == N) {
    for (i = 0; i < N; i++) buf[i] = comp((float)buf_short[i], 0.f);
    quisk_ccfFilter(buf, buf, N, bpf);
    /* we only output the real part in this test */
    for (i = 0; i < N; i++) buf_short[i] = buf[i].real;
    fwrite(buf_short, sizeof(short), N, stdout);
  }

  quisk_filt_destroy(bpf);
  free(bpf);
  return 0;
}

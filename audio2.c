#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "esd.h"

#define  WAV  "/home/pi/tes.wav"
#define  BUFFER  4096

static unsigned char  tmp[BUFFER];

int  main(void)
{
  FILE *fp;
  int vol, count, len;
  int esd;
  int sock = -1, rate = ESD_DEFAULT_RATE;
  esd_format_t format = 0;
  unsigned char *host = NULL;
  esd_info_t  *esdctl;

  format = ESD_BITS16 | ESD_STEREO | ESD_STREAM | ESD_PLAY;

  /* --- デバイスのオープン */
  esd = esd_open_sound(host);
  fp = fopen(WAV, "r");
  sock = esd_play_stream_fallback(format, rate, host, WAV);

  esdctl = esd_get_all_info(esd);

  /* --- 出力ループ */
  while((len = fread(tmp, 1, BUFFER, fp)) > 0) {
    write(sock, tmp, len);
  }
  esd_close(esd);
  fclose(fp);
  close(sock);
}

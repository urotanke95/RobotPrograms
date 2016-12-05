/*-------------------------------------------------------
  OSS - /dev/dsp  test
--------------------------------------------------------*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/soundcard.h>
#include <sys/types.h>
#include <sys/stat.h>

#define  DSP  "/dev/dsp"
#define  WAV  "/home/pi/tes.wav"
#define  BUFFER  2048

static unsigned char  tmp[BUFFER];

int  main(void)
{
  int fp, out;
  int len, format;

  /* --- デバイスのオープン */
  fp = open(WAV, O_RDONLY);
	if(fp == -1)printf("error open");
  out = open(DSP, O_WRONLY);
	if(out == -1)printf("error open");

  /* --- 音声デバイス設定 */
  format = AFMT_S16_LE;  
  if(ioctl(out, SNDCTL_DSP_SETFMT, &format)<0)printf("error SNDCTL_DSP_SETFMT\n");
  format = 1;
  if(ioctl(out, SNDCTL_DSP_STEREO, &format)<0)printf("error SNDCTL_DSP_SPEED\n");
  format = 8000;
  if(ioctl(out, SNDCTL_DSP_SPEED, &format)<0)printf("error SNDCTL_DSP_SPEED\n");
  /* --- 出力ループ */
  while((len = read(fp, tmp, BUFFER)) > 0) {
    write(out, tmp, len);
  }
	printf("close\n");
  close(fp);
  close(out);
}

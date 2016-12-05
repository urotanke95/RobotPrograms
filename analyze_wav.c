#include <stdio.h>
#include <string.h>
/* wavファイルヘッダー解析プログラム */
/* gcc -o wav wav.c */
/* ./wav sample.wav */
 
typedef struct{
  char            riff[4];          // RIFFヘッダ
  unsigned int    fileSize;         // ファイルサイズ - 8
  char            wave[4];          // WAVEヘッダ
} wavHeader;
 
typedef struct{
  unsigned char   fmt[4];           // fmt チャンク
   int   fmtSize;                   // fmt チャンクのバイト数
} tagChank;
 
typedef struct{
  unsigned short  id;        // フォーマットID
  unsigned short  channels;         // チャンネル数
  unsigned int    samplingRate;     // サンプリングレート
  unsigned int    bytesPerSec;      // データ速度 (Byte/sec)
  unsigned short  blockSize;       // ブロックサイズ
  unsigned short  bitsPerSample;    // サンプルあたりのビット数
} wavFormat;
 
int main(int argc,char *argv[]){
  FILE *fp;
  int i;
  wavHeader header;
  tagChank chank;
  wavFormat format;
 
  fp=fopen(argv[1],"rb");
 
  /*ヘッダー情報の読み取り*/
  fread(&header,sizeof(wavHeader),1,fp);
  header.riff[4]='\0';
  header.wave[4]='\0';
  printf("識別子             : %s\n",header.riff);
  printf("ファイルサイズ     : %d[bytes]\n",header.fileSize+8);
  printf("ファイル形式       : %s\n",header.wave);
 
  /*チャンクの読み取り*/
  fread(&chank,sizeof(chank),1,fp);
  long len =chank.fmtSize;
  chank.fmt[4]='\0';
  printf("fmt                : %s\n",chank.fmt);
  printf("fmtチャンクサイズ  : %ld[bytes]\n",len);
 
  /*各種フォーマットデータの読み取り*/
  fread(&format,sizeof(wavFormat),1,fp);
  printf("format ID(PCM=1)   : %d (0x%04x)\n",format.id,format.id);
  printf("チャンネル数       : %d (モノラル=1 ステレオ=2)\n",format.channels);
  printf("サンプリングレート : %d[Hz]\n",format.samplingRate);
  printf("データ速度         : %d[bytes/sec]\n",format.bytesPerSec);
  printf("ブロックサイズ     : %d[bytes]\n",format.blockSize);
  printf("量子化ビット数     : %d[bit]\n",format.bitsPerSample);
  printf("再生時間           : %.2f[sec]\n",(double)(header.fileSize+8)/format.bytesPerSec);
  fclose(fp);
	}

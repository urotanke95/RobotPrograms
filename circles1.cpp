#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"

using namespace cv;

int main (int argc, char **argv)
{
  CvCapture *capture = 0;
  double w =320,h=240;
  int c;
  int i;
  IplImage *src_img, *src_img_gray;
  CvMemStorage *storage;
  CvSeq *circles = 0;
  float *p;

  // (1)画像を読み込み
  if (argc == 1 || (argc >= 2 && strlen(argv[1])== 1 && isdigit (argv[1][0])))
    capture = cvCreateCameraCapture(argc==2?argv[1][0] - '0':0);

  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, w);
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, h);
  cvNamedWindow ("Circles", CV_WINDOW_AUTOSIZE); 

  while(1){
    src_img = cvQueryFrame(capture);
    src_img_gray = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U,1);
    Mat src_img_ = cvarrToMat(src_img);
    Mat src_img_gray_ = cvarrToMat(src_img_gray);
    cvtColor(src_img_, src_img_gray_, CV_RGB2GRAY);
    cvSmooth(src_img_gray, src_img_gray, CV_GAUSSIAN, 11,11,0,0);
    storage =cvCreateMemStorage(0);
    circles =cvHoughCircles(src_img_gray, storage, CV_HOUGH_GRADIENT, 2,10,160,50,10,20);

    for (i =0; i < circles->total; i++) {
      p = (float *) cvGetSeqElem(circles,i);
      cvCircle(src_img, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]),CV_RGB(255,0,0),3,8,0);
    }
    cvShowImage("Circles", src_img);
    c = cvWaitKey(2);
    if (c =='\x1b')
      break;
  }

  cvDestroyWindow ("Circles");
  cvReleaseCapture (&capture);
  cvReleaseImage (&src_img);
  cvReleaseImage (&src_img_gray);
  cvReleaseMemStorage(&storage);

  return 0;
}


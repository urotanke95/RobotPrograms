#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "stdio.h"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // デフォルトカメラをオープン
    if(!cap.isOpened())  // 成功したかどうかをチェック
        return -1;

    Mat brightness;
    namedWindow("brightness",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // カメラから新しいフレームを取得
        cv::cvtColor(frame, brightness, CV_BGR2GRAY);

        int intensity, max_intensity;
        int max_x, max_y;
        for( int y = 0; y < frame.rows; y++ ) {
            for( int x = 0; x < frame.cols; x++ ) {
                intensity = frame.at<unsigned char>(y, x); //X座標がx, Y座標がyに位置するピクセルの値を取得
                if(!(intensity>max_intensity)){continue;}
                // intensity is more than max_intensity
                max_intensity = intensity;
                max_x = x;
                max_y = y;
            }
        }
        printf("max is %d at %d,%d\n", max_intensity,max_x,max_y);
        imshow("brightness", brightness);
        if(waitKey(30) >= 0) break;
    }
    // VideoCapture デストラクタにより，カメラは自動的に終了処理されます
    return 0;
}

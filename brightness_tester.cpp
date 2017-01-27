#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "stdio.h"

using namespace cv;
unsigned char max_intensity = 0;
int target_x = 0;
int target_y = 0;

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

        unsigned char intensity = 0;

        for( int y = 0; y < frame.rows; y++ ) {
            for( int x = 0; x < frame.cols; x++ ) {
                intensity = frame.at<unsigned char>(y, x); //X座標がx, Y座標がyに位置するピクセルの値を取得
                if(intensity <= max_intensity){continue;}
                // intensity is more than max_intensity
                max_intensity = intensity;
                target_x = x;
                target_y = y;
            }
        }
        printf("max is %d at %d,%d\n", max_intensity,target_x,target_y);
        // 直線の描画(画像，始点，終点，色，線幅、連結する近傍数)
	    line(brightness, Point(brightness.cols / 2, brightness.rows), Point(target_x, target_y), Scalar(0,0,250), 3, 4);
        imshow("brightness", brightness);
        if(waitKey(30) >= 0) break;
    }
    // VideoCapture デストラクタにより，カメラは自動的に終了処理されます
    return 0;
}

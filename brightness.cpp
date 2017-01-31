#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "stdio.h"

using namespace cv;
unsigned char max_intensity = 0;
int target_x = 0;
int target_y = 0;
int window_x_center = 0;
int window_y_max = 0;

int main()
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
        window_x_center = brightness.cols/2;
        window_y_max = brightness.rows;
        unsigned char intensity = 0;

        for( int y = 0; y < brightness.rows; y++ ) {
            for( int x = 0; x < brightness.cols; x++ ) {
                intensity = brightness.at<unsigned char>(y, x); //X座標がx, Y座標がyに位置するピクセルの値を取得
                if(intensity <= max_intensity){continue;}
                // intensity is more than max_intensity
                max_intensity = intensity;
                target_x = x;
                target_y = y;
            }
        }
        printf("max is %d at %d,%d\n", max_intensity,target_x,target_y);
        // 直線の描画(画像，始点，終点，色，線幅、連結する近傍数)
	    line(brightness, Point(window_x_center, window_y_max), Point(target_x, target_y), Scalar(0,0,250), 3, 4);
        imshow("brightness", brightness);
        if(waitKey(30) >= 0) break;
    }
    // VideoCapture デストラクタにより，カメラは自動的に終了処理されます
    return 0;
}

int get_vec_x(){
    return target_x - window_x_center;
}
int get_vec_y(){
    // 座標系の関係で順番が逆
    return window_y_max - target_y;
}

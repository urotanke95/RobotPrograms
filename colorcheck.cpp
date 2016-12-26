// Module "core"
#include <opencv2/core/core.hpp>

// Module "highgui"
#include <opencv2/highgui/highgui.hpp>

// Module "imgproc"
#include <opencv2/imgproc/imgproc.hpp>

// Module "video"
#include <opencv2/video/video.hpp>

// Output
#include <iostream>

// Vector
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0); //capture the video from web cam

	int notFoundCount=0;
	bool found=false;

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	int measSize = 4;
	int stateSize = 6;
	int contrSize = 0;
	unsigned int type = CV_32F;
	KalmanFilter kf(stateSize, measSize, contrSize, type);
	Mat meas(measSize, 1, type);
	Mat state(stateSize, 1, type);

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

																									  //morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		

		vector<vector<cv::Point>> contours;
		findContours(imgThresholded, contours, CV_RETR_EXTERNAL,
			CV_CHAIN_APPROX_NONE);

		// >>>>> Filtering
		vector<vector<cv::Point> > balls;
		vector<cv::Rect> ballsBox;
		for (size_t i = 0; i < contours.size(); i++)
		{
			cv::Rect bBox;
			bBox = cv::boundingRect(contours[i]);

			float ratio = (float)bBox.height / (float)bBox.width;
			// Searching for a bBox almost square
			if (ratio > 2.0 && bBox.area() >= 400 && ratio <6.0)
			{
				balls.push_back(contours[i]);
				ballsBox.push_back(bBox);
			}
		}

		for (size_t i = 0; i < balls.size(); i++)
		{
			cv::drawContours(imgOriginal, balls, i, CV_RGB(20, 150, 20), 1);
			cv::rectangle(imgOriginal, ballsBox[i], CV_RGB(0, 255, 0), 2);

			cv::Point center;
			center.x = ballsBox[i].x + ballsBox[i].width / 2;
			center.y = ballsBox[i].y + ballsBox[i].height / 2;
			cv::circle(imgOriginal, center, 2, CV_RGB(20, 150, 20), -1);

			stringstream sstr;
			sstr << "(" << center.x << "," << center.y << ")";
			cv::putText(imgOriginal, sstr.str(),
				cv::Point(center.x + 3, center.y - 3),
				cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(20, 150, 20), 2);
			cout << center.x << ", " << center.y << endl;
		}

		if (balls.size() == 0)
		{
			notFoundCount++;
			cout << "notFoundCount:" << notFoundCount << endl;
			if (notFoundCount >= 100)
			{
				found = false;
			}
			/*else
			kf.statePost = state;*/
		}
		else
		{
			notFoundCount = 0;

			meas.at<float>(0) = ballsBox[0].x + ballsBox[0].width / 2;
			meas.at<float>(1) = ballsBox[0].y + ballsBox[0].height / 2;
			meas.at<float>(2) = (float)ballsBox[0].width;
			meas.at<float>(3) = (float)ballsBox[0].height;

			if (!found) // First detection!
			{
				// >>>> Initialization
				kf.errorCovPre.at<float>(0) = 1; // px
				kf.errorCovPre.at<float>(7) = 1; // px
				kf.errorCovPre.at<float>(14) = 1;
				kf.errorCovPre.at<float>(21) = 1;
				kf.errorCovPre.at<float>(28) = 1; // px
				kf.errorCovPre.at<float>(35) = 1; // px

				state.at<float>(0) = meas.at<float>(0);
				state.at<float>(1) = meas.at<float>(1);
				state.at<float>(2) = 0;
				state.at<float>(3) = 0;
				state.at<float>(4) = meas.at<float>(2);
				state.at<float>(5) = meas.at<float>(3);
				// <<<< Initialization

				found = true;
			}
			else
				kf.correct(meas); // Kalman Correction

								  //cout << "Measure matrix:" << endl << meas << endl;
		}

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;

}
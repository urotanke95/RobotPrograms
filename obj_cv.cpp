#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
//#include "move_api.h"

#define CAMERA_U_IDX 0
#define CAMERA_F_IDX 0
#define PIX_LEN 300

using namespace cv;
using namespace cv::face;
using namespace std;

string fn_haar = "/usr/local/Cellar/opencv3/3.2.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
string fn_csv = "/Users/okuokakouhei/java/eclipse/RobotCV/face.csv";

extern "C" static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
        return;
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

extern "C" int searchObj(char* color) {
	 // >>>> Kalman Filter
	int stateSize = 6;
	int measSize = 4;
	int contrSize = 0;
	//g_init();

	unsigned int type = CV_32F;
	cv::KalmanFilter kf(stateSize, measSize, contrSize);

	cv::Mat state(stateSize, 1, type);  // [x,y,v_x,v_y,w,h]
	cv::Mat meas(measSize, 1, type);    // [z_x,z_y,z_w,z_h]
										//cv::Mat procNoise(stateSize, 1, type)
										// [E_x,E_y,E_v_x,E_v_y,E_w,E_h]

										// Transition State Matrix A
										// Note: set dT at each processing step!
										// [ 1 0 dT 0  0 0 ]
										// [ 0 1 0  dT 0 0 ]
										// [ 0 0 1  0  0 0 ]
										// [ 0 0 0  1  0 0 ]
										// [ 0 0 0  0  1 0 ]
										// [ 0 0 0  0  0 1 ]
	cv::setIdentity(kf.transitionMatrix);

	// Measure Matrix H
	// [ 1 0 0 0 0 0 ]
	// [ 0 1 0 0 0 0 ]
	// [ 0 0 0 0 1 0 ]
	// [ 0 0 0 0 0 1 ]
	kf.measurementMatrix = cv::Mat::zeros(measSize, stateSize, type);
	kf.measurementMatrix.at<float>(0) = 1.0f;
	kf.measurementMatrix.at<float>(7) = 1.0f;
	kf.measurementMatrix.at<float>(16) = 1.0f;
	kf.measurementMatrix.at<float>(23) = 1.0f;

	// Process Noise Covariance Matrix Q
	// [ Ex   0   0     0     0    0  ]
	// [ 0    Ey  0     0     0    0  ]
	// [ 0    0   Ev_x  0     0    0  ]
	// [ 0    0   0     Ev_y  0    0  ]
	// [ 0    0   0     0     Ew   0  ]
	// [ 0    0   0     0     0    Eh ]
	//cv::setIdentity(kf.processNoiseCov, cv::Scalar(1e-2));
	kf.processNoiseCov.at<float>(0) = 1e-2;
	kf.processNoiseCov.at<float>(7) = 1e-2;
	kf.processNoiseCov.at<float>(14) = 5.0f;
	kf.processNoiseCov.at<float>(21) = 5.0f;
	kf.processNoiseCov.at<float>(28) = 1e-2;
	kf.processNoiseCov.at<float>(35) = 1e-2;

	// Measures Noise Covariance Matrix R
	cv::setIdentity(kf.measurementNoiseCov, cv::Scalar(1e-1));
	// <<<< Kalman Filter

	cv::VideoCapture cap(CAMERA_F_IDX);//デバイスのオープン

	if(!cap.isOpened()){   //読み込みに失敗したときの処理
		return -1;
	}
	cv::Mat frame;
	cv::Mat res;
	cv::Rect bBoxmax;

	double ticks = 0;
	bool found = false;
	int notFoundCount = 0;
//	g_init();
	while(1) {
		cap >> frame;
		frame.copyTo(res);

		double precTick = ticks;
		ticks = (double)cv::getTickCount();
		double dT = (ticks - precTick) / cv::getTickFrequency(); //seconds

		if (found) {
			// >>>> Matrix A
			kf.transitionMatrix.at<float>(2) = dT;
			kf.transitionMatrix.at<float>(9) = dT;
			// <<<< Matrix A

			//cout << "dT:" << endl << dT << endl;

			state = kf.predict();
			//cout << "State post:" << endl << state << endl;

			cv::Rect predRect;
			predRect.width = state.at<float>(4);
			predRect.height = state.at<float>(5);
			predRect.x = state.at<float>(0) - predRect.width / 2;
			predRect.y = state.at<float>(1) - predRect.height / 2;

			cv::Point center;
			center.x = state.at<float>(0);
			center.y = state.at<float>(1);
			cv::circle(res, center, 2, CV_RGB(255, 0, 0), -1);

			cv::rectangle(res, predRect, CV_RGB(255, 0, 0), 2);
		}

		// >>>>> Noise smoothing
		cv::Mat blur;
		cv::GaussianBlur(frame, blur, cv::Size(5, 5), 3.0, 3.0);
		// <<<<< Noise smoothing

		// >>>>> HSV conversion
		cv::Mat frmHsv;
		cv::cvtColor(blur, frmHsv, CV_BGR2HSV);
		// <<<<< HSV conversion

		// >>>>> Color Thresholding
		cv::Mat rangeRes = cv::Mat::zeros(frame.size(), CV_8UC1);
		cv::inRange(frmHsv, cv::Scalar(100, 150, 50),cv::Scalar(170, 255, 255), rangeRes);
		// <<<<< Color Thresholding

		// >>>>> Improving the result
		cv::erode(rangeRes, rangeRes, cv::Mat(), cv::Point(-1, -1), 2);
		cv::dilate(rangeRes, rangeRes, cv::Mat(), cv::Point(-1, -1), 2);
		// <<<<< Improving the result

		std::vector<std::vector<cv::Point> > contours;
		cv::findContours(rangeRes, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		cv::Rect bBox;

		std::vector<cv::Point> max;
		std::vector<std::vector<cv::Point> > resultbox;
		if (contours.size() == 0) {
		//  g_turn(0, 100);

		} else {
			max = contours[0];
			bBoxmax = cv::boundingRect(max);
			bBox = bBoxmax;

			for (size_t i = 0; i < contours.size(); i++) {
			   bBox = cv::boundingRect(contours[i]);
			   if (bBox.area() > bBoxmax.area()){
				   bBoxmax = bBox;
				   max = contours[i];
			   }
			}

			resultbox.push_back(max);

			cv::drawContours(res, resultbox, 0, CV_RGB(0, 255, 0), 1);
			cv::rectangle(res, bBoxmax, CV_RGB(0, 255, 0), 2);

		}

		// >>>>> Kalman Update
		if (resultbox.size() == 0) {
		//	X = 1300;
		//	Y = 800;
			notFoundCount++;
			if (notFoundCount >= 100) {
				found = false;
			}
		} else {
			notFoundCount = 0;

			meas.at<float>(0) = bBoxmax.x + bBoxmax.width / 2;
			meas.at<float>(1) = bBoxmax.y + bBoxmax.height / 2;
			meas.at<float>(2) = (float)bBoxmax.width;
			meas.at<float>(3) = (float)bBoxmax.height;

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
			} else {
				kf.correct(meas); // Kalman Correction
			}
		}

		cv::imshow("Threshold", res);

		int key = cv::waitKey(1);
		if(key == 113)//qボタンが押されたとき
		{
			break;//whileループから抜ける．
		}
	}

	cv::destroyAllWindows();
//	g_quit();
	return 0;
}

extern "C" int searchUser(int uid) {
 	vector<Mat> images;
	vector<int> labels;
	try {
		read_csv(fn_csv, images, labels);
	} catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		return -1;
	}

	int im_width = images[0].cols;
	int im_height = images[0].rows;

	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	model->train(images, labels);

	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);

	VideoCapture cap(CAMERA_U_IDX);
	if(!cap.isOpened()) {
		cerr << "Capture Device cannot be opened." << endl;
		return -1;
	}

	Mat frame;
	for(;;) {
		cap >> frame;
		Mat original = frame.clone();
		Mat gray;
		cvtColor(original, gray, CV_BGR2GRAY);

		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(gray, faces);

		Rect max = faces[0];

		for(int i = 0; i < faces.size(); i++) {
			if (faces[i].area() < max.area()) {
				continue;
			}
			max = faces[i];
		}
		Rect face_i = max;
		Mat face = gray(face_i);

		Mat face_resized;
		cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
		int prediction = model->predict(face_resized);
		rectangle(original, face_i, CV_RGB(0, 255,0), 1);
		string box_text = format("Prediction = %d", prediction);

		int pos_x = std::max(face_i.tl().x - 10, 0);
		int pos_y = std::max(face_i.tl().y - 10, 0);

		putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);

		// Show the result:
		imshow("face_recognizer", original);
		// And display it:
		char key = (char) waitKey(20);
		// Exit this loop on escape:
		if(key == 27)
			break;
	}
	cv::destroyAllWindows();
	return 0;
}

int main(int argh, char* argv[]) {
	int test = atoi(argv[1]);
	if (test == 1) { //User
		searchUser(atoi(argv[2]));
	} else if (test == 2) { //Object
		searchObj(argv[2]);
	}
	return 0;
}





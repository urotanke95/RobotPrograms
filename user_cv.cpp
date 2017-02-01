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
#define DEBUG 1

using namespace cv;
using namespace cv::face;
using namespace std;

string fn_haar = "/usr/local/Cellar/opencv3/3.2.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
string fn_csv = "/Users/okuokakouhei/java/eclipse/RobotCV/face.csv";
Ptr<FaceRecognizer> model;
CascadeClassifier haar_cascade;
int im_width, im_height;
cv::VideoCapture cap;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
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

int search(int uid){
	if(!cap.isOpened()) {
		cerr << "Capture Device cannot be opened." << endl;
		return -1;
	}
	Mat frame;
	cap >> frame;
	Mat original = frame.clone();
//	Rect base = cv::boundingRect(original);
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
	if (prediction != uid) {
		return 0;
	}
	int center_x = face_i.x + face_i.width / 2;
	int center_y = face_i.y + face_i.height / 2;


	if (DEBUG == 1) {
		rectangle(original, face_i, CV_RGB(0, 255,0), 1);
		string box_text = format("Prediction = %d", prediction);
		int pos_x = std::max(face_i.tl().x - 10, 0);
		int pos_y = std::max(face_i.tl().y - 10, 0);
		putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
		imshow("face_recognizer", original);
	}
	return 0;
}

int init() {
	vector<Mat> images;
	vector<int> labels;
	try {
		read_csv(fn_csv, images, labels);
	} catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		return -1;
	}

	im_width = images[0].cols;
	im_height = images[0].rows;

	model = createFisherFaceRecognizer();
	model->train(images, labels);

	haar_cascade.load(fn_haar);
	cap = VideoCapture(CAMERA_U_IDX);
	return 0;
}

int main(int argh, char* argv[]) {
	init();
	while(1) {
		search(2);
		char key = (char) waitKey(40);
		if(key == 27)
			break;
	}
	cv::destroyAllWindows();
	return 0;
}





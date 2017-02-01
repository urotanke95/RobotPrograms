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

#define CAMERA_U_IDX 0
#define PIX_LEN 300

using namespace cv;
using namespace cv::face;
using namespace std;

string fn_haar = "/usr/local/Cellar/opencv3/3.2.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
string fn_csv = "/Users/okuokakouhei/java/eclipse/RobotCV/face.csv";

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

static void write_csv(const string& filename, vector<string>& paths, int uid) {
	std::ofstream writing_file;
	writing_file.open(filename, std::ios::app);
	if (!writing_file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
		return;
	}

	for (int i = 0; i< paths.size(); i++) {
	    writing_file << paths[i] << ";" << uid << "\n";
	}
	writing_file << std::flush;
}

int registerUser(int uid, const char *name){
	VideoCapture cap(0);
	if(!cap.isOpened()) {
		return -1;
	}
	Mat image;
	string csv_file = "/Users/okuokakouhei/java/eclipse/RobotCV/face.csv";
	string imagepath = "/Users/okuokakouhei/java/eclipse/RobotCV/images/";
	imagepath += name;
	if(mkdir(imagepath.c_str(), 0755)==0){
	   printf("フォルダ作成に成功しました。\n");
	}else{
	   printf("フォルダ作成に失敗しました。\n");
	}
	imagepath += "/";

	vector<string> paths;
	int count = 0;
	while(1) {
		cap >> image;
		string cascade_file = "/usr/local/Cellar/opencv3/3.2.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";

		CascadeClassifier cascade;
		cascade.load(cascade_file);

		vector<Rect> faces;
		cascade.detectMultiScale(image, faces, 1.1,3,0,Size(20,20));
		Rect bmax;

		for (int i = 0; i < faces.size(); i++){
			bmax = faces[0];
			for (size_t i = 1; i < faces.size(); i++) {
				if (faces[i].area() > bmax.area()){
					bmax = faces[i];
				}
			}
		}

		if (faces.size() == 0) {
			continue;
		}
		cv::Mat roi_img(image, bmax);
		rectangle(image, bmax,Scalar(0,200,0),3,CV_AA);
		double y = (double)PIX_LEN / bmax.height;
		double x = (double)PIX_LEN / bmax.width;
		resize(roi_img, roi_img, Size(), x, y, INTER_CUBIC);
		imshow("detect face",image);
		char key = (char) waitKey(0);
		if(key == 27) { //ESC
			break;
		} else if (key == 32){ //Space
			string imgname = imagepath;
			imgname += name;
			imgname += to_string(count);
			imgname += ".jpg";
			std::cout << "Print:" << imgname << std::endl;
			imwrite(imgname, roi_img);
			paths.push_back(imgname);
			count++;
		} else {

		}
	}
	cv::destroyAllWindows();
	if (paths.size() > 0) {
		write_csv(csv_file, paths, uid);
	}
	return 0;
}

int main(int argh, char* argv[]) {
	if (argh != 3) {
		fprintf(stderr, "./ [UID] [name]");
	}
	registerUser(atoi(argv[1]), argv[2]);
	return 0;
}





#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//Function prototyping
Mat findCentroid(Mat src, Mat real);
void capture(int camera, int frameRate);
Mat rename(Mat src);

int main(int argv, char** argc) {
	if (argv > 1) {
		cout << argv;
		cout << "Running video capture mode" << endl;
		capture(0, 60);	
	}

	cout << "Running image processing mode" << endl;

	return 0;
}
Mat rename(Mat src) {
	Mat hsv;
	Mat mask;

	cvtColor(src, hsv, COLOR_BGR2HSV);

	Scalar lowerLimit = Scalar(1, 150, 160);
	Scalar upperLimit = Scalar(45, 255, 255);
	inRange(hsv,lowerLimit, upperLimit, mask);

	return mask;
}
void image(string filepath) {
	Mat image = imread(filepath);

	//Check for failure
	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		cin.get();
		return;
	}

	//Create window
	namedWindow("image");
	imshow("image", image);
	waitKey(0);
	destroyWindow("image");
}

void capture(int camera, int frameRate) {
	int wait = 1000 / frameRate; //calculates how long to show frame in video
	Mat frame;

	VideoCapture cap(0);
	cap.open(0, CAP_ANY);

	if (!cap.isOpened()) {
		cout << "Camera cannot be found." << endl;
	}

	while (cap.read(frame)) {
		if (frame.empty()) {
			cerr << "Empty Frame." << endl;
		}
		Mat outline = rename(frame);
		Mat outline2;
		Mat dst;
		Mat final;
		blur(outline, dst, Size(5, 5), Point(-1, -1));
		double thresh = 0;
		threshold(dst, outline2, thresh, 255, THRESH_BINARY_INV);
		final = findCentroid(outline2, frame);
		imshow("Camera", final);
		if (waitKey(wait) >= 10) {
			//cout << "why" << endl;
			continue;
		}	
	}	
}

Mat findCentroid(Mat src, Mat real) {
	//Mat variables
	Mat gray = src;

	//im
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	 
	// detect edges using canny
	Canny(gray, canny_output, 50, 150, 3);
	 
	// find contours
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	 
	// get the moments
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		mu[i] = moments(contours[i], false);
	}
	 
	// get the centroid of figures.
	vector<Point2f> mc(contours.size());
	for (int i = 0; i<contours.size(); i++) {
		mc[i] = Point2f(mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00);
	}
	 
	// draw contours
	Mat drawing(canny_output.size(), CV_8UC3, Scalar(255,255,255));
	Point center(drawing.rows / 2, drawing.cols / 2);
	string message;
	for(int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(167,151,0); // B G R values
		drawContours(real, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle( real, mc[i], 4, color, -1, 8, 0 );
		if (i == 0 ) {
		int x = (int) mc[0].x;
		int y = (int) mc[0].y;
		switch (x / center.x) {
			case 0:
				message += "left";
				break;
			case 1:
				message += "right";
				break;
			default:
				message += "right";
				break;
		}
		message += " ";
		switch (y / center.y) {
			case 0:
				message += "up";
				break;
			case 1:
				message += "down";
				break;
			default:
				message += "down";
				break;
		}
		putText(real, message, center, FONT_HERSHEY_DUPLEX, 1, color, 2);
		//cout << "x: " << mc[i].x << ", y: " << mc[i].y << endl;
		}
	}


	return real;	 
}




#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;

void sobelTransform_Gx(Mat image, Mat sobel_Gx){

	int intensity;

	for(int row = 1; row < image.rows - 1; row++){
		for(int col = 1; col < image.cols - 1; col++){
			intensity = 0;
			intensity += (int) image.at<uchar>(row - 1, col + 1) + (int) 2*image.at<uchar>(row, col + 1) + (int) image.at<uchar>(row + 1, col + 1);	
			intensity -= (int) image.at<uchar>(row - 1, col - 1) + (int) 2*image.at<uchar>(row, col - 1) + (int) image.at<uchar>(row + 1, col - 1);
			sobel_Gx.at<int>(row, col) = intensity;
		}	
		
	}

}

void sobelTransform_Gy(Mat image, Mat sobel_Gy){
	
	int intensity;
	
	for(int row = 1; row < image.rows - 1; row++){
		for(int col = 1; col < image.cols - 1; col++){
			intensity = 0;
			intensity = (int) image.at<uchar>(row - 1, col - 1) + (int) image.at<uchar>(row - 1, col)*2 + (int) image.at<uchar>(row - 1, col + 1);
			intensity -= (int) image.at<uchar>(row + 1, col - 1) + (int) image.at<uchar>(row + 1, col)*2 + (int) image.at<uchar>(row + 1, col + 1);
			sobel_Gy.at<int>(row, col) = intensity;
		}
	
	}

}

void sobel_Magnitude(Mat sobel_Mag, Mat sobel_Gx, Mat sobel_Gy){
	float intensity;
	float normalizer = 4*sqrt(2);
	for (int row = 0; row < sobel_Mag.rows; row++){
		for(int col = 0; col < sobel_Mag.cols; col++){
			intensity = sobel_Gx.at<int>(row, col)*sobel_Gx.at<int>(row, col) + sobel_Gy.at<int>(row, col)*sobel_Gy.at<int>(row, col);
			intensity /= normalizer;
			sobel_Mag.at<uchar>(row, col) = uchar(intensity);
		}
	
	}

}

void sobel_Angle(Mat sobel_Ang, Mat sobel_Gx, Mat sobel_Gy){
	float pi = 2*cos(0.0);
	float intensity;
	float normalizer = 255/pi;
	for (int row = 0; row < sobel_Ang.rows; row++){
		for(int col = 0; col < sobel_Ang.cols; col++){
			intensity = (float) sobel_Gy.at<int>(row, col) / (float) sobel_Gx.at<int>(row, col);
			intensity = atan(intensity);
			intensity += pi/2;
			/*
			intensity *= intensity;
			intensity = sqrt(intensity);
			intensity *= 2;*/
			intensity *= normalizer;
			sobel_Ang.at<uchar>(row, col) = uchar(intensity);
		}
	
	}

}


int main(){
	thread t1;
	thread t2;

	Mat image = imread("tower.jpg", IMREAD_GRAYSCALE);
	
	if (image.empty()){
		cout << "Could not load Image" << '\n';
		cin.get();
		return - 1;
	
	}

	Mat sobel_Gx(image.rows, image.cols, CV_32SC1, Scalar(0));
	Mat sobel_Gy(image.rows, image.cols, CV_32SC1, Scalar(0));
	Mat sobel_Mag(image.rows, image.cols, CV_8UC1, uchar(0));
	Mat sobel_Ang(image.rows, image.cols, CV_8UC1, uchar(0));
	
	if (image.empty()){
		cout << "Could not find image" << '\n';
		cin.get();
		return -1;
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	t1 = thread(sobelTransform_Gx, image, sobel_Gx);
	t2 = thread(sobelTransform_Gy, image, sobel_Gy);
	t1.join();
	t2.join();

	t1 = thread(sobel_Magnitude, sobel_Mag, sobel_Gx, sobel_Gy);
	t2 = thread(sobel_Angle, sobel_Ang, sobel_Gx, sobel_Gy);
	t1.join();
	t2.join();
	
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	cout << "Time taken for computations " << elapsed_seconds.count() << "s\n";
	
	imwrite("Sobel Absolute Values.jpg", sobel_Mag);
	imwrite("Sobel Angles not absoluted.jpg", sobel_Ang);
	
	String windowMagnitude = "Magnitude";
	String windowAngle = "Angle";
	namedWindow(windowMagnitude, WINDOW_NORMAL);
	namedWindow(windowAngle, WINDOW_NORMAL);
	imshow(windowMagnitude, sobel_Mag);
	imshow(windowAngle, sobel_Ang);
	waitKey(0);
	destroyWindow(windowMagnitude);
	destroyWindow(windowAngle);

}

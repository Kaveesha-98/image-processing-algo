#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

using namespace cv;
using namespace std;

Mat sobelTransform(Mat image){
	
	Mat sobel(image.rows, image.cols, CV_8UC1, Scalar(0));
	
	int intensity = 0;
	
	for(int row = 1; row < image.rows - 1; row++){
		for(int col = 1; col < image.cols - 1; col++){
			intensity = (int) image.at<uchar>(row - 1, col + 1) + (int) image.at<uchar>(row, col + 1)*2 + (int) image.at<uchar>(row + 1, col + 1);
			intensity -= (int) image.at<uchar>(row - 1, col - 1) + (int) image.at<uchar>(row, col - 1)*2 + (int) image.at<uchar>(row + 1, col - 1);
			intensity += 1020;
			intensity /= 8;
			sobel.at<uchar>(row, col) = uchar(intensity);
			
		}
	
	}
	
	return sobel;
}


int main(){
	Mat image = imread("tower.jpg", IMREAD_GRAYSCALE);
	
	if(image.empty()){
		cout << "Could not find image" << '\n';
		cin.get();
		return -1;	
	}
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	Mat sobel = sobelTransform(image);	
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Time taken for sobel transformation = " << elapsed_seconds.count() << "s\n";
	
	String windowName = "Image";
	imwrite("sobelTransform_Gy.jpg", sobel);
	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, sobel);
	waitKey(0);
	destroyWindow(windowName);
}

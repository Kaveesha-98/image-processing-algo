#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;

void vertical_convolution(Mat image, Mat vertical_convl, int *colNo, int kernal_size){
	
	int intensity;
	int start_row = kernal_size/2 + 1;
	
	for(int col = 0; col < image.cols; col++){
		intensity = 0;
		
		/*
		for(int i = 0; i < kernal_size; i++){
			intensity += image.at<uchar>(i, col);
			
		}
		vertical_convl.at<uchar>(start_row, col) = uchar(intensity/kernal_size);
		*/
		
		for(int row = start_row; row < image.rows - start_row; row++){
			intensity = 0;
			for(int r = row - kernal_size/2; r < row + kernal_size/2; r++){
				intensity += (int) image.at<uchar>(r , col);
			
			}
			vertical_convl.at<uchar>(row, col) = uchar(intensity/kernal_size);
			/*
			intensity = intensity - image.at<uchar>(row - start_row, col) + image.at<uchar>(row + start_row - 1, col);
			vertical_convl.at<uchar>(row, col) = uchar(intensity/kernal_size);
			*/
		}
		(*colNo) += 1;
	}

}

void horizontal_convolution(Mat vertical_convl, Mat blurred, int *colNo, int kernal_size){
	
	int intensity;
	int start_col = kernal_size/2 + 1;
	bool start_convolution = false;
	
	cout << *colNo;
	
	while(!start_convolution){
		if(*colNo > kernal_size){
			start_convolution = true;
		
		}
	
	}
	
	for (int row = 0; row < vertical_convl.rows; row++){
		intensity = 0;
		for(int col = 0; col < kernal_size; col++){
			intensity += (int) vertical_convl.at<uchar>(row, col);
		}
		blurred.at<uchar>(row, start_col) = uchar(intensity/kernal_size);
		
	}
	
	for(int col = start_col + 1; col < vertical_convl.cols - start_col; col++){
		while(*colNo < col + kernal_size && *colNo < vertical_convl.cols){
			//cout << *colNo << ' ' << col << '\n';
		}
		for (int row = 0; row < vertical_convl.rows; row++){
			//blurred.at<uchar>(row, col) = vertical_convl.at<uchar>(row, col+ start_col - 1);
			intensity = 0;
			for (int i = col - kernal_size/2; i <= col + kernal_size/2; i++){
				intensity += (int) vertical_convl.at<uchar>(row, i); 
			}
			blurred.at<uchar>(row, col) = uchar(intensity/kernal_size);
		/*
			intensity = (int) blurred.at<uchar>(row, col - 1);
			intensity *= kernal_size;
			intensity = intensity - vertical_convl.at<uchar>(row, col - start_col) + vertical_convl.at<uchar>(row, col + start_col - 1);
			blurred.at<uchar>(row, col) = uchar(intensity/kernal_size);
		*/
		}
		
	
	}

}


//hriztl
int main(){
	thread t1;
	thread t2;
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	
	Mat image = imread("tower.jpg", IMREAD_GRAYSCALE);
	int kernal_size = 41;
	
	if(image.empty()){
		cout << "Could not find image\n";
		cin.get();
		return -1;
	}
	
	Mat vertical_convl(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat blurred(image.rows, image.cols, CV_8UC1, Scalar(0));
	int colNo = 0;
	
	start = std::chrono::system_clock::now();
	t1 = thread(vertical_convolution, image, vertical_convl, &colNo, kernal_size);
	t2 = thread(horizontal_convolution, vertical_convl, blurred, &colNo, kernal_size);
	t1.join();
	t2.join();
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	cout << "Time taken for convolution with kernal " << kernal_size << 'x' << kernal_size << " is " << elapsed_seconds.count() << "s\n";
	
	String windowName = "image";
	namedWindow(windowName, WINDOW_NORMAL);
	imwrite("test.jpg", blurred);
	imshow(windowName, blurred);
	waitKey(0);
	destroyWindow(windowName);
	
}

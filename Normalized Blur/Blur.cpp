#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;

int main(){
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	
	Mat image = imread("tower.jpg", IMREAD_GRAYSCALE);
	if (image.empty()){
		cout << "Could not load Image" << '\n';
		cin.get();
		return - 1;
	
	}
	Mat Blur(image.rows, image.cols, CV_8UC1, Scalar(0));
	
	int kernal_size = 21;
	int start_row = kernal_size/2 + 1;
	int start_col = start_row;
	int intensity;
	
	start = std::chrono::system_clock::now();
	for(int row = start_row; row < image.rows; row++){
		for(int col = start_col; col < image.cols; col++){
			intensity = 0;
			for (int kernal_row = 1 - start_row; kernal_row < kernal_size - start_row; kernal_row++){
				for (int kernal_col = 1 - start_col; kernal_col < kernal_size - start_col; kernal_col++){
					intensity += (int) image.at<uchar>(row + kernal_row, col + kernal_col);
				}
			}
			intensity /= kernal_size*kernal_size;
			Blur.at<uchar>(row, col) = uchar(intensity);
		}
	
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Time taken for convolution with kernal " << kernal_size << 'x' << kernal_size << " is " << elapsed_seconds.count() << "s\n";
	//imwrite("Not Blurred.jpg", image);
	//imwrite("Blurred with 21x21 kernal.jpg", Blur);
	String windowName = "Blur";
	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, Blur);
	waitKey(0);
	destroyWindow(windowName);

}

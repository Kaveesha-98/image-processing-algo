#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace cv;
using namespace std;

int main(int argc, char** argv){

	Mat hists(3, 256, CV_32SC1, Scalar(0));//used to calculate histograms
	
	Mat image = imread("tower.jpg", IMREAD_COLOR);
	
	if(image.empty()){
		cout << "Could not open or find image" << '\n';
		cin.get();
		return -1;	
	}
	
	//int intensity = image.at<uint8_t>(1, 1, 2);
	
	String windowName = "Tower";//Name of the window
	
	namedWindow(windowName, WINDOW_NORMAL);//creating a window
	
	imshow(windowName, image);//Showing the image inside created window
	
	waitKey(0);//Wait for any keystroke in the window
	
	destroyWindow(windowName);//destroy the created window
	
	uchar y;
	int x;
	Vec3b intensity = image.at<Vec3b>(0, 0);
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	//calculating historgram
	for(int j= 0; j < image.rows; j++){
		for (int i = 0; i < image.cols; i++){
			intensity = image.at<Vec3b>(j, i);
			for (int n = 0; n < 3; n++){
				y = intensity.val[n];
				x = int(y);
				hists.at<int>(n, x) += 1;
			}
		}
	}
	//culumilaing histogram
	for(int i = 1; i < 256; i++){
		for (int j = 0; j < 3; j++){
			hists.at<int>(j, i) += hists.at<int>(j, i - 1);
		}
	}
	double l;
	//normalizing
	for(int i = 0; i < 256; i++){
		for (int j = 0; j < 3; j++){
			x = hists.at<int>(j, i);
			l = (double) x*255;
			hists.at<int>(j, i) = l/hists.at<int>(j, 255);
		}
	}
	//intensity transformtion
	for(int j= 0; j < image.rows; j++){
		for (int i = 0; i < image.cols; i++){
			intensity = image.at<Vec3b>(j, i);
			for (int n = 0; n < 3; n++){
				y = intensity.val[n];
				x = int(y);
				x = hists.at<int>(n, x);
				y = uchar(x);
				image.at<Vec3b>(j, i).val[n] = y;
			}
		}
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Time taken for histogram equalization = " << elapsed_seconds.count() << "s\n";
	//String windowName = "Tower";//Name of the window
	
	namedWindow(windowName, WINDOW_NORMAL);//creating a window
	
	imshow(windowName, image);//Showing the image inside created window
	
	waitKey(0);//Wait for any keystroke in the window
	
	imwrite("histogram equalized.jpg", image);//saving image
	
	destroyWindow(windowName);//destroy the created window
}

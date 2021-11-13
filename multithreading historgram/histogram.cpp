#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

using namespace cv;
using namespace std;

void histogramEqualized(Mat image, int channel){

	Mat hists(1, 256, CV_32SC1, Scalar(0));//used to calculate the histogram
	uchar intensity;
	int index;
	//calculating histogram
	for(int j = 0; j < image.rows; j++){
		for(int i = 0; i < image.cols; i++){
			intensity = image.at<Vec3b>(j, i).val[channel];
			index = int(intensity);		
			hists.at<int>(index) += 1;
		}
	
	}
	
	int k;
	//culumulating histogram	
	for(int index = 1; index < 256; index++){
		hists.at<int>(index) += hists.at<int>(index - 1);
		//cout << hists.at<int>(index)<< '\n';
	}	

	//int normalizer = hists.at<int>(254);
	k = hists.at<int>(255);
	int cumul_hist;
	long normalized_hist;
	int l;

	for(int index = 0; index < 256; index++){
		int cumul_hist = hists.at<int>(index);
		normalized_hist = (double) cumul_hist*255/k;
		hists.at<int>(index) = normalized_hist;	
	}
	
	for(int j= 0; j < image.rows; j++){
		for (int i = 0; i < image.cols; i++){
			image.at<Vec3b>(j, i);
			intensity = image.at<Vec3b>(j, i).val[channel];
			k = int(intensity);
			image.at<Vec3b>(j, i).val[channel] = uchar(hists.at<int>(k));
		}
	}

}


int main(int argc, char** argv){
	thread t1;
	thread t2;
	thread t3;

	Mat image = imread("tower.jpg", IMREAD_COLOR);
	
	if(image.empty()){
		cout << "Could not open or find image" << '\n';
		cin.get();
		return -1;	
	}
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	t1 = thread(histogramEqualized, image, 0);
	t2 = thread(histogramEqualized, image, 1);
	t3 = thread(histogramEqualized, image, 2);
	t1.join();
	t2.join();
	t3.join();
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Time taken for histogram equalization = " << elapsed_seconds.count() << "s\n";
	String windowName = "Tower";//Name of the window
	
	namedWindow(windowName, WINDOW_NORMAL);//creating a window
	
	imshow(windowName, image);//Showing the image inside created window
	
	waitKey(0);//Wait for any keystroke in the window
	
	imwrite("histogram equalized.jpg", image);//saving image
	
	destroyWindow(windowName);//destroy the created window
}

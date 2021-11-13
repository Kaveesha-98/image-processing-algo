//Loading the cv classes and cin cout classes
#include <opencv2/opencv.hpp>
#include <iostream>

//using the ablive classes as namespace
using namespace cv;
using namespace std;

int main(int argc, char** argv){
	
	//Reading image file
	Mat image = imread("tower.jpg");
	
	if(image.empty()){
		cout << "Could not open or find image" << '\n';
		cin.get();//waiting for a key press;
		return -1;
	}
	int m = image.at<uint8_t>(image.rows - 1, image.cols - 1, 0);
	//m = image.cols;
	
	cout << m;
	String windowName = "Tower";//Name of the window
	
	namedWindow(windowName, WINDOW_NORMAL);//creating a window
	
	imshow(windowName, image);//Showing the image inside created window
	
	waitKey(0);//Wait for any keystroke in the window
	
	destroyWindow(windowName);//destroy the created window
	return 0;	
	
	
}

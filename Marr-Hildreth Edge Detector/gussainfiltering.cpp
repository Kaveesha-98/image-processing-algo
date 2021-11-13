#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <math.h>

using namespace std;
using namespace cv;

void vertical_convolution(Mat image, Mat buffer, int kernal_size, int normalize, int kernal[], int *horizontal_convolution_row){

	int pixel;
	int intensity;
	int start_row = kernal_size/2;

	for(int row = start_row; row < image.rows - start_row - 1; row++){
		while(*horizontal_convolution_row - start_row<= row){
			//waiting
		}
		for(int col = 0; col < image.cols; col++){
			intensity = 0;
			for(int kernal_index = 0; kernal_index < kernal_size; kernal_index++){
				pixel = (int) buffer.at<uchar>(row - start_row + kernal_index, col);
				intensity += pixel*kernal[kernal_index];
			}
			intensity /= normalize;
			image.at<uchar>(row, col) = uchar(intensity);
		}	
	}

}
/*
void applyBuffer(Mat buffer, Mat image, int *horizontal_convolution_row){
	for (int row = 0; row < image.rows - 1; row++){
		while (*horizontal_convolution_row <= row){
			//waiting
		}
		for(int col = 0; col < image.cols; col++){
			image.at<uchar>(row, col) = buffer.at<uchar>(row, col);
		
		}
*/

void horizontal_convolution(Mat image, Mat buffer, int kernal_size, int normalize, int kernal[], int *horizontal_convolution_row){
	int start_col = kernal_size/2;
	int intensity = 0;
	int pixel;
	
	for (int row = 0; row < image.rows; row++){
		*horizontal_convolution_row  = row;
		for(int col = start_col; col < image.cols - start_col - 1; col++){
			intensity = 0;
			for (int kernal_index = 0; kernal_index < kernal_size; kernal_index++){
				pixel = (int) image.at<uchar>(row, col - start_col + kernal_index);
				intensity += pixel*kernal[kernal_index];
			}
			intensity /= normalize;
			buffer.at<uchar>(row, col) = uchar(intensity);
		}
	}

}

void create_kernal(int kernal[], int kernal_size, double sigma, int *normalize){
	int kernal_mid_index = kernal_size/2;
	//const double pi = 3.14159265358979323846;
	double kernal_corner_x_2 = (double) kernal_mid_index*kernal_mid_index;
	double kernal_corner = exp(-1*kernal_corner_x_2/(2*sigma*sigma));//(2*pi*sigma*sigma);
	double kernal_value_at_index_double;
	double x_2;
	double sigma_2 = sigma*sigma;
	int k = 0;
	//*normalize = 2;
	
	kernal[0] = 1;
	kernal[kernal_size - 1] = 1;
	kernal_value_at_index_double = 1.0;
	kernal[kernal_mid_index] = (int) kernal_value_at_index_double/kernal_corner;
	normalize += kernal[kernal_mid_index];
	
	for (int x = 1; x < kernal_mid_index; x++){
		x_2 = (double) x*x;
		kernal_value_at_index_double = exp(-1*x_2/(2*sigma_2));
		//cout << " " << kernal_value_at_index_double << " " << kernal_corner << " ";
		kernal_value_at_index_double = kernal_value_at_index_double/kernal_corner;
		kernal[kernal_mid_index - x] = (int) round(kernal_value_at_index_double);
		kernal[kernal_mid_index + x] = kernal[kernal_mid_index - x];
		//cout << kernal_value_at_index_double << '\n'; 
		k += 2*kernal[kernal_mid_index - x];
	}
	//*normalize = k;
	//return normalize;

}


int main(){
	thread thread_horizontal_convolution;
	thread thread_vertical_convolution;
	//thread thread_apply_buffer;

	Mat image = imread("tower.jpg", IMREAD_GRAYSCALE);
	
	if(image.empty()){
		cout << "Could not find image\n";
		cin.get();
		return -1;	
	}
	
	Mat buffer(image.rows, image.cols, CV_8UC1, Scalar(0));
	
	int kernal_size = 19;
	double sigma = 3;
	int normalize;
	
	int kernal [kernal_size];
	int *kernal_address = kernal;
	
	create_kernal(kernal, kernal_size, sigma, &normalize);
	int horizontal_convolution_row;
	cout << kernal[1] << " ";
	
	normalize = 0;
	
	for (int i = 0; i<kernal_size; i++){
		cout << " " << kernal[i];
		normalize += kernal[i];
	}
	
	cout << " " << normalize;
	
	//horizontal_convolution(image, buffer, kernal_size, normalize, kernal_address, &horizontal_convolution_row);
	
	thread_horizontal_convolution = thread(horizontal_convolution, image, buffer, kernal_size, normalize, kernal_address, &horizontal_convolution_row);
	thread_vertical_convolution = thread(vertical_convolution, image, buffer, kernal_size, normalize, kernal_address, &horizontal_convolution_row);
	//thread_apply_buffer = thread(applyBuffer, buffer, image, &horizontal_convolution_row);
	thread_horizontal_convolution.join();
	thread_vertical_convolution.join();
	//thread_apply_buffer.join();
	
	String windowName = "image";
	namedWindow(windowName, WINDOW_NORMAL);
	imwrite("blurred image kernal 41x41 sigma = 4.jpg", image);
	imshow(windowName, image);
	waitKey(0);
	destroyWindow(windowName);
	
	Mat secondDerivative(image.rows, image.cols, CV_32SC1, int(0));
	
	int new_intensity;
	int pixel;
	
	for(int row = 1; row < image.rows - 1; row++){
		for(int col = 1; col < image.cols - 1; col++){
			new_intensity = 0;
			for(int kernal_row = -1; kernal_row <= 1; kernal_row++){
				for(int kernal_col = -1; kernal_col <= 1; kernal_col++){
					new_intensity += (int) image.at<uchar>(row + kernal_row, col + kernal_col);
				}
			}
			pixel = (int) image.at<uchar>(row, col);
			new_intensity = new_intensity - 9*pixel;
			secondDerivative.at<int>(row, col) = new_intensity;
		}
	}
	
	bool neighbours[3][3];
	int max_pixel = 0;
	
	for(int row = 1; row < image.rows - 1; row++){
		for(int col = 1; col < image.cols - 1; col++){
			for(int kernal_row = -1; kernal_row <= 1; kernal_row++){
				for(int kernal_col = -1; kernal_col <= 1; kernal_col++){
					pixel = (int) secondDerivative.at<int>(row + kernal_row, col + kernal_col);
					neighbours[kernal_row + 1][kernal_col + 1] = pixel < 0;
				}
			}
			pixel  = 0;
			new_intensity = 0;
			if(neighbours[0][0] ^ neighbours[2][2]){
				pixel = secondDerivative.at<int>(row - 1, col - 1) - secondDerivative.at<int>(row + 1, col + 1);
				if(pixel < 0){
					pixel = 0 - pixel;
				}
			}
			if(neighbours[0][1] ^ neighbours[2][1]){
				new_intensity = secondDerivative.at<int>(row - 1, col) - secondDerivative.at<int>(row + 1, col);
				if(new_intensity < 0){
					new_intensity = 0 - new_intensity;
				}
				if(pixel < new_intensity){
					pixel = new_intensity;
				}
			}
			if(neighbours[0][2] ^ neighbours[2][0]){
				new_intensity = secondDerivative.at<int>(row - 1, col + 1) - secondDerivative.at<int>(row + 1, col - 1);
				if(new_intensity < 0){
					new_intensity = 0 - new_intensity;
				}
				if(pixel < new_intensity){
					pixel = new_intensity;
				}
			}
			if(neighbours[1][0] ^ neighbours[1][2]){
				new_intensity = secondDerivative.at<int>(row, col - 1) - secondDerivative.at<int>(row, col + 1);
				if(new_intensity < 0){
					new_intensity = 0 - new_intensity;
				}
				if(pixel < new_intensity){
					pixel = new_intensity;
				}
			}
			if(pixel > max_pixel){
				max_pixel = pixel;
				cout << max_pixel << endl;
			}
			if(pixel > 10){
				image.at<uchar>(row, col) = uchar(255);
			}
			else{
				image.at<uchar>(row, col) = uchar(0);
			}

		}
	}
	
	namedWindow(windowName, WINDOW_NORMAL);
	imwrite("zero_crossing.jpg", image);
	imshow(windowName, image);
	waitKey(0);
	destroyWindow(windowName);
	
	for(int row = 1; row < image.rows - 1; row++){
		for(int col = 1; col < image.cols - 1; col++){
			if((int) image.at<uchar>(row - 1, col - 1) == 255){
				continue;
			} else if((int) image.at<uchar>(row - 1, col) == 255){
				continue;
			} else if((int) image.at<uchar>(row - 1, col + 1) == 255){
				continue;
			} else if((int) image.at<uchar>(row, col - 1) == 255){
				continue;
			} else if((int) image.at<uchar>(row, col + 1) == 255){
				continue;
			} else if((int) image.at<uchar>(row + 1, col - 1) == 255){
				continue;
			} else if((int) image.at<uchar>(row + 1, col) == 255){
				continue;
			} else if((int) image.at<uchar>(row + 1, col + 1) == 255){
				continue;
			} else{
				image.at<uchar>(row - 1, col) = uchar(0);
			}
		}
	}
	
	namedWindow(windowName, WINDOW_NORMAL);
	imwrite("zero_crossing cleared.jpg", image);
	imshow(windowName, image);
	waitKey(0);
	destroyWindow(windowName);
}

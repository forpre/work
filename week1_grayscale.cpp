#include <opencv2/opencv.hpp> 
#include <iostream> 

using namespace cv;

int main()
{
	Mat srcMat = imread("D:\\picture\\0.jpg",0);
	imshow("src", srcMat);
	waitKey(0);
}

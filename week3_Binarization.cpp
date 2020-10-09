#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat result;
	Mat result_1;
	Mat srcMat = imread("D:\\picture\\123.jpg", 0);
	if (!srcMat.data)
	{
		cout << "图像不能载入" << endl;
		return 0;
	}

	threshold(srcMat,result,100,255,THRESH_BINARY);
	adaptiveThreshold(srcMat,result_1,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,25,10);

	imshow("原图",srcMat);
	imshow("二值化", result);
	imshow("局部自适应二值化", result_1);
	waitKey(0);
}

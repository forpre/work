#include <opencv2/opencv.hpp> 
#include <iostream> 

using namespace cv;

int main()
{
	Mat srcMat = imread("D:\\picture\\0.jpg");
	Mat shallowMat = srcMat;
	Mat deepMat;
	srcMat.copyTo(deepMat);
	int height = srcMat.rows;
	int width = srcMat.cols;
	uchar average = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			uchar threshold = 150;
			if ((threshold < (srcMat.at<Vec3b>(i, j)[0] + srcMat.at<Vec3b>(i, j)[1] + srcMat.at<Vec3b>(i, j)[2]) / 3))
			{
				average = 255;
			}
			else
			{
				average = 0;
			}
			srcMat.at<Vec3b>(i, j)[0] = average;
			srcMat.at<Vec3b>(i, j)[1] = average;
			srcMat.at<Vec3b>(i, j)[2] = average;
		}
	}
	imshow("src", srcMat);
	imshow("shallow",shallowMat);
	imshow("deep",deepMat);
	waitKey(0);
}

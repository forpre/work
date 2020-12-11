#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;


int main()
{

	Mat srcMat = imread("D:\\picture\\21.jpg",1);
	//通道分离
	vector<Mat>channels;
	split(srcMat, channels);

	//直方图均衡
	equalizeHist(channels.at(0), channels.at(0));
	equalizeHist(channels.at(1), channels.at(1));
	equalizeHist(channels.at(2), channels.at(2));

	//通道合成
	Mat dstMat;
	srcMat.copyTo(dstMat);
	merge(channels,dstMat);

	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
	waitKey(0);
}

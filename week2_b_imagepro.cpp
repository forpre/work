#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main()
{
	cv::Point pt;
	cv::Point pt1;
	cv::Point pt2;
	cv::Rect rect;
	cv::Mat dispMat(1000,1000,CV_8UC3,Scalar(255,0,0));
	pt.x = 400;
	pt.y = 300;
	circle(dispMat, pt, 100, CV_RGB(255, 0, 0), 1, 8, 0);//»­Ô²
	pt1.x = 100;
	pt1.y = 100;
	pt2.x = 200;
	pt2.y = 200;
	line(dispMat, pt1, pt2, CV_RGB(255,0,0),1,8,0);//»­Ïß
	rect.x = 50;
	rect.y = 50;
	rect.width = 10;
	rect.height = 10;
	rectangle(dispMat,rect,CV_RGB(255,0,0),1,8,0);//»­¾ØÐÎ
	imshow("disp_rectangle", dispMat);
	waitKey(0);
	return 0;
}

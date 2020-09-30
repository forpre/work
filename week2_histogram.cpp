#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("D:\\picture\\timg.jpg"); //加载并显示原图
	int height = srcMat.rows; //行数
	int width = srcMat.cols; //每行像素的总像素数量
	float histgram[256] = {0};
	Mat dstimage(256, 256, CV_8U, Scalar(255));
	int c;
	int count;
	for (int j = 0; j<height; j++) //遍历像素
	{ 
		for (int i = 0; i<width; i++) 
		{ 
			int gray = saturate_cast<uchar>(srcMat.at<Vec3b>(j,i)[2]*0.2989+ srcMat.at<Vec3b>(j, i)[1] * 0.5870+ srcMat.at<Vec3b>(j, i)[0] * 0.1140);//RGB转灰度值
			histgram[gray] = histgram[gray] + 1; 
		}	//单行处理结束 
		waitKey(0);
	} 
	for ( c = 0; c < 256; c++)
	{
		histgram[c] = histgram[c] / (height*width);
	}
	Point pt1;
	Point pt2;
	int scale = 1300;
	for (count = 0; count < 256; count++)
	{
		pt1.x = count;
		pt1.y = 256;
		pt2.x = count;
		pt2.y = 256-histgram[count] * scale;
		line(dstimage,pt1,pt2,CV_RGB(255,0,0),1,8,0);
	}
	imshow("直方图",dstimage);
	waitKey(0);
}

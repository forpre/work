#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("D:\\picture\\123.jpg"); //加载并显示原图
	int height = srcMat.rows; //行数
	int width = srcMat.cols; //每行像素的总像素数量
	float histgram[256] = {0}; //存储数值个数
	float Redch[256] = { 0 };
	float Greench[256] = { 0 };
	float Bluech[256] = { 0 };
	Mat dstimage(256, 256, CV_8UC3, Scalar(255,255,255));//各通道图像
	Mat Redimage(256, 256, CV_8UC3, Scalar(255,255,255));
	Mat Greenimage(256, 256, CV_8UC3, Scalar(255,255,255));
	Mat Blueimage(256, 256, CV_8UC3, Scalar(255,255,255));
	int c;
	int count;
	for (int j = 0; j<height; j++) //遍历像素，统计个数
	{ 
		for (int i = 0; i<width; i++) 
		{ 
			int gray = saturate_cast<uchar>(srcMat.at<Vec3b>(j,i)[2]*0.2989+ srcMat.at<Vec3b>(j, i)[1] * 0.5870+ srcMat.at<Vec3b>(j, i)[0] * 0.1140);//RGB转灰度值
			histgram[gray]++; 
			Redch[srcMat.at<Vec3b>(j, i)[2]]++;
			Greench[srcMat.at<Vec3b>(j, i)[1]]++;
			Bluech[srcMat.at<Vec3b>(j, i)[0]]++;
		}	//单行处理结束 
	} 
	int scale = 5000; //刻度
	//归一化处理
	for ( c = 0; c < 256; c++)
	{
		histgram[c] = histgram[c] / (height*width);
		Redch[c] = Redch[c] / (height*width);
		Greench[c] = Greench[c] / (height*width);
		Bluech[c] = Bluech[c] / (height*width);

		//画出直方图
		line(dstimage, Point(c, 256), Point(c, 256 - histgram[c] * scale), CV_RGB(0, 0, 0), 1, 8, 0);
		line(Redimage, Point(c, 256), Point(c, 256 - Redch[c] * scale), CV_RGB(255, 0, 0), 1, 8, 0);
		line(Greenimage, Point(c, 256), Point(c, 256 - Greench[c] * scale), CV_RGB(0, 255, 0), 1, 8, 0);
		line(Blueimage, Point(c, 256), Point(c, 256 - Bluech[c] * scale), CV_RGB(0, 0, 255), 1, 8, 0);
	}
	imshow("灰度值直方图",dstimage);
	imshow("红色直方图", Redimage);
	imshow("绿色直方图", Greenimage);
	imshow("蓝色直方图", Blueimage);
	waitKey(0);
}

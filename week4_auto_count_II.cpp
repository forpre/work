#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("D:\\picture\\14.jpg", 0);//取图像
	Mat result;
	Mat result_cnet;
	Mat stats;
	Mat centroid;
	Rect rect;
	Point anchor = Point(-1, -1);//锚点
	Rect rect1(75, 0, srcMat.cols-75, srcMat.rows); //将左边一部分截去,保证计数正确
	Mat image = srcMat(rect1);
	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(5, 5), anchor);	//5*5矩形结构
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(15, 15), anchor);	//15*15矩形结构

	image.copyTo(result);
	threshold(image, result, 100, 255, THRESH_BINARY_INV);//反向阈值二值化  
	threshold(result, result, 100, 255, THRESH_OTSU);//大津二值化  

	result.copyTo(result_cnet);
	int coin_num = connectedComponentsWithStats(result, result_cnet, stats, centroid, 8, CV_32S);//连通域标记
	for (int i = 0; i < stats.rows - 1; i++)
	{
		rect.x = stats.at<int>(i + 1, CC_STAT_LEFT); //状态矩阵赋值
		rect.y = stats.at<int>(i + 1, CC_STAT_TOP);
		rect.width = stats.at<int>(i + 1, CC_STAT_WIDTH);
		rect.height = stats.at<int>(i + 1, CC_STAT_HEIGHT);
		rectangle(result, rect, CV_RGB(255, 255, 255), 1, 8, 0); //画外接矩形
	}
	
	cout << "回形针:" << stats.rows - 1 << endl;  //显示个数

	imshow("结果图", result);//显示原图与对圆点自动计数的图
	imshow("原图", srcMat);
	waitKey(0);
	return 0;
}

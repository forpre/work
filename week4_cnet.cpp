#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("D:\\picture\\12.jpg", 0);//取图像
	Mat result;
	Mat result_cnet;
	Mat stats;
	Mat centroid;
	Rect rect;

	srcMat.copyTo(result);
	threshold(srcMat, result, 100, 255, THRESH_BINARY);//正向二值化
	result.copyTo(result_cnet);
	int coin_num = connectedComponentsWithStats(result,result_cnet,stats,centroid,8,CV_32S);//连通域标记
	for (int i = 0; i < stats.rows - 1; i++)
	{
		rect.x = stats.at<int>(i + 1, CC_STAT_LEFT); //状态矩阵赋值
		rect.y = stats.at<int>(i + 1, CC_STAT_TOP);
		rect.width = stats.at<int>(i + 1, CC_STAT_WIDTH);
		rect.height = stats.at<int>(i + 1, CC_STAT_HEIGHT);
		rectangle(result,rect,CV_RGB(255,255,255),1,8,0); //画外接矩形
	}
	cout << "硬币个数：" << coin_num - 1 << endl;//显示硬币个数

	imshow("结果图", result);//显示原图与绘制外接四边形后的图
	imshow("原图",srcMat);
	waitKey(0);
	return 0;
}

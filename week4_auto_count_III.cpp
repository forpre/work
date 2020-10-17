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

	srcMat.copyTo(result);
	threshold(result, result, 100, 255, THRESH_BINARY_INV);//反向阈值二值化  
	threshold(result, result, 100, 255, THRESH_OTSU);//大津二值化  

	result.copyTo(result_cnet);
	int coin_num = connectedComponentsWithStats(result, result_cnet, stats, centroid, 8, CV_32S);//连通域标记

	int count = 0;
	for (int j = 0; j < stats.rows - 1; j++)//根据外界四边形长宽判断是否为回形针
	{
		if ((stats.at<int>(j + 1, CC_STAT_WIDTH)>50 && stats.at<int>(j + 1, CC_STAT_WIDTH)<250) && (stats.at<int>(j + 1, CC_STAT_HEIGHT)>50 && stats.at<int>(j + 1, CC_STAT_HEIGHT)<250))
		{
			count++;
			rect.x = stats.at<int>(j + 1, CC_STAT_LEFT); //状态矩阵赋值
			rect.y = stats.at<int>(j + 1, CC_STAT_TOP);
			rect.width = stats.at<int>(j + 1, CC_STAT_WIDTH);
			rect.height = stats.at<int>(j + 1, CC_STAT_HEIGHT);
			rectangle(result, rect, CV_RGB(255, 255, 255), 1, 8, 0); //画外接矩形
		}
	}

	cout << "回形针个数:" << count << endl;  //显示个数

	imshow("结果图", result);//显示原图与对圆点自动计数的图
	imshow("原图", srcMat);
	waitKey(0);
	return 0;
}

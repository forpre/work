#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("D:\\picture\\13.jpg", 0);//取图像
	Mat result;
	Mat result_cnet;
	Mat stats;
	Mat centroid;
	Rect rect;
	Point anchor = Point(-1, -1);//锚点
	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(25, 25), anchor);	//25*25矩形结构

	srcMat.copyTo(result);
	threshold(srcMat, result, 100, 255, THRESH_BINARY_INV);//反向阈值二值化  
	threshold(result, result, 100, 255,THRESH_OTSU);//大津二值化  

	//先用25*25矩形腐蚀
	morphologyEx(result, result, 0, kernel1, anchor, 1, BORDER_CONSTANT);

	//再用25*25矩形膨胀
	morphologyEx(result, result, 1, kernel1, anchor, 1, BORDER_CONSTANT);


	result.copyTo(result_cnet);
	int coin_num = connectedComponentsWithStats(result, result_cnet, stats, centroid, 8, CV_32S);//连通域标记

	cout << "圆孔个数:" << coin_num - 1 << endl;  //显示个数

	imshow("结果图", result);//显示原图与对圆点自动计数的图
	imshow("原图", srcMat);
	waitKey(0);
	return 0;
}

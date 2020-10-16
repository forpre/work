#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void main()
{
	Mat srcMat = imread("D:\\picture\\12.jpg",0);//取图像
	Mat result;
	Mat result_erode;
	Mat result_dilate;
	Mat result_open;
	Mat result_close;
	Point anchor = Point(-1, -1);//锚点
	Mat kernel = getStructuringElement(MORPH_RECT,Size(10,10),anchor);	//25*25矩形结构


	threshold(srcMat,result,100,255,THRESH_BINARY);//局部自适应法二值化
	morphologyEx(result,result_erode,0,kernel,anchor,1,BORDER_CONSTANT);//腐蚀，膨胀，开运算，闭运算
	morphologyEx(result,result_dilate, 1, kernel, anchor, 1, BORDER_CONSTANT);
	morphologyEx(result,result_open, 2, kernel, anchor, 1, BORDER_CONSTANT);
	morphologyEx(result,result_close, 3, kernel, anchor, 1, BORDER_CONSTANT);


	imshow("result",result);  //显示原图，腐蚀、膨胀、开运算、闭运算后的图
	imshow("result_erode",result_erode);
	imshow("result_dilate", result_dilate);
	imshow("result_open", result_open);
	imshow("result_close", result_close);
	waitKey(0);
}

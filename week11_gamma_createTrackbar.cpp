#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/*查表法实现gamma变换算法*/
Mat gammaTransform(Mat &srcImage, float gamma)
{
	//建立查询表
	unsigned char LUT[256] = { 0 };
	for (int i = 0; i < 256; i++)
	{
		float f = (float)i / 255;
		f = (float)(pow(f, gamma));
		LUT[i] = saturate_cast<uchar>(f*255.0f);
	}
	Mat resultImage;
	srcImage.copyTo(resultImage);

	//根据图像通道数分别进行gamma校正
	if (srcImage.channels() == 1)
	{
		for (int i = 0; i < srcImage.rows; i++)
		{
			uchar *data = resultImage.ptr<uchar>(i);
			for (int j = 0; j < srcImage.cols; j++)
			{
				data[j] = LUT[data[j]];
			}
		}
	}
	else
	{
		for (int i = 0; i < srcImage.rows; i++)
		{
			for (int j = 0; j < srcImage.cols; j++)
			{
				resultImage.at<Vec3b>(i, j)[0] = LUT[resultImage.at<Vec3b>(i, j)[0]];
				resultImage.at<Vec3b>(i, j)[1] = LUT[resultImage.at<Vec3b>(i, j)[1]];
				resultImage.at<Vec3b>(i, j)[2] = LUT[resultImage.at<Vec3b>(i, j)[2]];
			}
		}
	}
	return resultImage;
}

/*回调函数，实现对某一个图像的gamma校正*/
void gamma(int gamma,void*)
{
	Mat srcMat = imread("D:\\picture\\c1.jpg", 1);
	Mat dstMat;

	float scale = 100;//刻度缩放
	
	float gamma_1 = gamma / scale;

	//gamma变换
	dstMat = gammaTransform(srcMat, gamma_1);

	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
}

/*实现滑动条控制gamma参数，找到图像最佳gamma点*/
int main()
{
	int minth = 0;//滑动条初始值
	int maxth = 50;//滑动条最大值
	
	//回调函数创造滑动条
	namedWindow("dstMat_1",WINDOW_AUTOSIZE);
	createTrackbar("gamma","dstMat_1",&minth,maxth,gamma);

	waitKey(0);
}

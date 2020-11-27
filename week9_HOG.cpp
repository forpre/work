#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//计算HOG函数
int calcHOG(Mat src, float *Hist, int nAngle, int cellsize)
{
	//计算各个图片梯度与角度并转换成极坐标形式
	Mat gx, gy;
	Mat mag, angle;

	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	//各个图像cell划分
	int nx = src.cols / cellsize;
	int ny = src.rows / cellsize;


	//角度方向量化，图像分割成cell并绘制每个cell的直方图，最后组合成最终的直方图
	Rect roi(0, 0, cellsize, cellsize);
	for (int i = 0; i < ny; i++)
	{
		for (int j = 0; j < nx; j++)
		{
			Mat roiMat(src.rows,src.cols,CV_8UC1);
			Mat roiMag(src.rows, src.cols, CV_8UC1);
			Mat roiAgl(src.rows, src.cols, CV_8UC1);

			roi.x = j*cellsize;
			roi.y = i*cellsize;
			//赋值图像
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//当前cell第一个元素在直方图数组中的位置
			int head = (i*nx + j)*nAngle;

			//绘制每个cell直方图并将组合成总直方图
			for (int n = 0; n < roiMat.rows; n++)
			{
				uchar* Agl = roiAgl.ptr<uchar>(n);
				uchar* Mag = roiMag.ptr<uchar>(n);
				for (int m = 0; m < roiMat.cols; m++)
				{
					int c = (int)Agl[m] / 45;
					Hist[head + c] += (float)Mag[m];
				}
			}
		}
	}

	return 0;
}

//计算欧几里得距离
float normL2(float *sHist, float *dHist, int bins)
{
	float distance = 0;
	for (int i = 0; i < bins; i++)
	{
		distance += pow((sHist[i] - dHist[i]),2);
	}
	distance = sqrt(distance);

	return distance;
}

int main()
{
	Mat refMat = imread("D:\\picture\\a2.jpg",0);
	Mat plMat = imread("D:\\picture\\a3.jpg",0);
	Mat bgMat = imread("D:\\picture\\a1.jpg",0);

	imshow("第一张图", refMat);
	imshow("第二张图", plMat);
	imshow("第三张图", bgMat);

	int cellsize = 16;//每个cell大小
	int nAngle = 8;//角度量分为8份
	//各个图像cell划分
	int nx = refMat.cols / cellsize;
	int ny = refMat.rows / cellsize;

	//动态分配内存建立动态数组
	int bins = nx*ny*nAngle;
	cout << "数组大小："+bins << endl;

	float * ref_hist = new float[bins];
	memset(ref_hist,0,sizeof(float)*bins);

	float * pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float)*bins);

	float * bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float)*bins);

	int reCode = 0;
	//计算三张输入的HOG
	reCode = calcHOG(refMat,ref_hist,nAngle, cellsize);
	reCode = calcHOG(plMat, pl_hist, nAngle, cellsize);
	reCode = calcHOG(bgMat, bg_hist, nAngle, cellsize);

	if (reCode != 0)
	{
		delete[] ref_hist;//释放内存
		delete[] pl_hist;
		delete[] bg_hist;
		return -1;
	}

	//计算直方图距离
	float dis1 = normL2(ref_hist,pl_hist,bins);
	float dis2 = normL2(ref_hist,bg_hist,bins);

	if (dis1 < dis2)
	{
		cout << "第二张图更接近第一张图" << endl;
	}
	else
	{
		cout << "第三张图更接近第一张图" << endl;
	}
	
	delete[] ref_hist;//释放内存
	delete[] pl_hist;
	delete[] bg_hist;
	waitKey(0);
	return 0;
}

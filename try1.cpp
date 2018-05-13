
//#include "stdafx.h" 
//
//#include <opencv2/opencv.hpp>
//
//
//
//using namespace std;
//
//using namespace cv;
//
//
//
//int main(int argc, char* argv[])
//
//{
//	int a = 0;
//	const char* imagename = "1.jpg";
//
//	IplImage* pImg;
//
//	if ((pImg = cvLoadImage("1.jpg", CV_LOAD_IMAGE_ANYCOLOR)) == 0) 
//		return 0;
//
//	//cvNamedWindow("柯南", 1);
//	cvShowImage("what?", pImg);
//
//
//
//
//
//	//此函数等待按键，按键盘任意键就返回
//
//	waitKey();
//
//	cvDestroyWindow("hh");
//	cvReleaseImage(&pImg);
//	return 0;
//
//}








//#include "stdafx.h" 
//#include<opencv2/core.hpp>  
//#include<opencv2/highgui.hpp>  
//#include<opencv2/imgproc.hpp>  
//
//#include<iostream>  
//#include<string> 
//
//using namespace cv;
//using namespace std;
//
//Mat img;                           //输入图像  
//Mat bgr;                           //灰度值归一化
//Mat hsv;						   //HSV图像  
//
//int hmin = 0;					   //色相  
//int hmin_Max = 360;
//int hmax = 360;
//int hmax_Max = 360;
//  
//int smin = 0;					   //饱和度
//int smin_Max = 255;
//int smax = 255;
//int smax_Max = 255;
// 
//int vmin = 106;					   //亮度 
//int vmin_Max = 255;
//int vmax = 250;
//int vmax_Max = 255;
//
//string windowName = "src";        //显示原图的窗口  
//string dstName = "dst";			  //输出图像的显示窗口  
//Mat dst;						  //输出图像 
//
//
//void callBack(int, void*)		  //回调函数  
//{
//	dst = Mat::zeros(img.size(), CV_32FC3);		//输出图像分配内存 
//	  
//	Mat mask;									//掩码
//	/*hsv为输入矩阵 mask为输出二值矩阵*/
//	inRange(hsv, Scalar(hmin, smin / float(smin_Max), vmin / float(vmin_Max)), Scalar(hmax, smax / float(smax_Max), vmax / float(vmax_Max)), mask);
//	//inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
//
//	for (int r = 0; r < bgr.rows; r++)//只保留  
//	{
//		for (int c = 0; c < bgr.cols; c++)
//		{
//			if (mask.at<uchar>(r, c) == 255)
//			{
//				dst.at<Vec3f>(r, c) = bgr.at<Vec3f>(r, c);
//			}
//		}
//	}
//	
//	imshow(dstName, dst);                 //输出图像    
//	dst.convertTo(dst, CV_8UC3, 255.0, 0);//保存图像
//	imwrite("HSV_inRange.jpg", dst);
//}
//
//
////int main(int argc, char*argv[])
//int main()
//{
//	//char argv[8];
//	//argv = "1.jpg";
//	img = imread("s.jpg", IMREAD_COLOR);  //输入图像  3通道rgb读取
//
//	if (!img.data || img.channels() != 3)
//	{
//		cout << "读取图像失败" << endl;
//		return -1;
//	}
//		
//	imshow(windowName, img);                       //显示原图像      
//	img.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);    //彩色图像的灰度值归一化 ？为什么1.0 / 255
//	//img.convertTo(bgr, CV_32FC3, 1.0, 0);
//	cvtColor(bgr, hsv, COLOR_BGR2HSV);             //颜色空间转换，将bgr色彩空间转化为hsv色彩空间
//	//imshow("bgr", bgr);
//	//imshow("hsv", hsv);
//
//	namedWindow(dstName, WINDOW_GUI_EXPANDED);     //定义输出图像的显示窗口  
//
//	//调节色相 H  
//	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
//	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);
//	//调节饱和度 S  
//	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
//	createTrackbar("smax", dstName, &smax, smax_Max, callBack);
//	//调节亮度 V  
//	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
//	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);
//	//callBack(0, 0);
//	waitKey(0);
//	return 0;
//}




/*
imrang是否可以不针对hsv的挑选
如果有针对那就写转化*/
#include "stdafx.h" 
#include<opencv2/core.hpp>  
#include<opencv2/highgui.hpp>  
#include<opencv2/imgproc.hpp>  

#include<iostream>  
#include<string> 

using namespace cv;
using namespace std;

#define HUE_MAX         360
#define	SATURATION_MAX  100
#define VALUE_MAX       100
#define R_MAX		    255
#define G_MAX		    255
#define B_MAX			255

typedef int Hsv_type;

Mat img; 
Mat dst;
Mat hsv;

Hsv_type hue_min = 0;
Hsv_type hue_max = HUE_MAX;
Hsv_type saturation_min = 0;
Hsv_type saturation_max = SATURATION_MAX;
Hsv_type value_min = 0;
Hsv_type value_max = VALUE_MAX;

//int r_min = 2345;
//int r_max = 255;
//int g_min = 0;
//int g_max = 255;
//int b_min = 0;
//int b_max = 255;

float hue;
float saturation;
float value;

//Vec3f colour1(0, 0, 0);
//Vec3f colour2(255, 255, 255);

string windowName = "原图像";        //显示原图的窗口  
string dstName = "dst";			  //输出图像的显示窗口  


void callBack(int, void*);
void Change_rgb2hvs(int r, int g, int b);
template<typename T>
T Find_max(T a, T b, T c);
template<typename T>
T Find_min(T a, T b, T c);


int main()
{
	img = imread("try.png", IMREAD_COLOR); 

	if (!img.data || img.channels() != 3)
	{
		cout << "读取图像失败" << endl;
		return -1;
	}
		
	imshow(windowName, img);                       //显示原图像      
	namedWindow(dstName, WINDOW_GUI_EXPANDED);     //定义输出图像的显示窗口  

	img.convertTo(img, CV_32FC3, 1.0 / 255, 0);    //彩色图像的灰度值归一化
	cvtColor(img, hsv, COLOR_BGR2HSV);             //颜色空间转换，将bgr色彩空间转化为hsv色彩空间


	 
	//createTrackbar("R_min", dstName, &r_min, R_MAX, callBack);
	//createTrackbar("R_max", dstName, &r_max, R_MAX, callBack);

	//createTrackbar("G_min", dstName, &g_min, G_MAX, callBack);
	//createTrackbar("G_max", dstName, &g_max, G_MAX, callBack);

	//createTrackbar("B_min", dstName, &b_min, B_MAX, callBack);
	//createTrackbar("B_max", dstName, &b_max, B_MAX, callBack);

	createTrackbar("H_min", dstName, &hue_min, HUE_MAX, callBack);
	createTrackbar("H_max", dstName, &hue_max, HUE_MAX, callBack);

	createTrackbar("S_min", dstName, &saturation_min, SATURATION_MAX, callBack);
	createTrackbar("S_max", dstName, &saturation_max, SATURATION_MAX, callBack);

	createTrackbar("V_min", dstName, &value_min, VALUE_MAX, callBack);
	createTrackbar("V_max", dstName, &value_max, VALUE_MAX, callBack);

	callBack(0, 0);
	waitKey(0);
	return 0;

	//Change_rgb2hvs(85, 198, 67);
	//cout << hue <<" "<<saturation <<" "<< value << endl;
}


void callBack(int, void*)		
{
	dst = Mat::zeros(img.size(), CV_32FC3);									
	
	//inRange(img, Scalar(b_min, g_min, r_min), Scalar(b_max, g_max, r_max), dst);
	inRange(hsv, Scalar(hue_min, (float)saturation_min / (float)SATURATION_MAX, (float)value_min / (float)VALUE_MAX), Scalar(hue_max, (float)saturation_max / (float)SATURATION_MAX, (float)value_max / (float)VALUE_MAX), dst);
	
	imshow(dstName, dst);                   //输出图像    
	dst.convertTo(dst, CV_8UC3, 255.0, 0);  //保存图像
	imwrite("HSV_inRange.jpg", dst);
}


void Change_rgb2hvs(int r_,int g_,int b_)
{
	float max = 0;
	float min = 0;
	float h_ = 0;
	float r = (float)r_ / 255.0;
	float b = (float)b_ / 255.0;
	float g = (float)g_ / 255.0;

	max = Find_max<float>(r, g, b);
	min = Find_min<float>(r, g, b);
	value = max;
	saturation = (max - min) / max;

	if (r == max)
	{
		h_ = (g - b) / (max - min);
	}
	else if (g == max)
	{
		h_ = 2 + (b - r) / (max - min);
	}
	else
	{
		h_ = 4 + (r - g) / (max - min);
	}

	if (h_ >= 0)
	{
		hue = h_ * 60.0;
	}
	else
	{
		hue = h_ * 60.0 + 360;
	}
}


template<typename T>
T Find_max(T a=0,T b=0,T c=0)
{
	if (a > b && a > c)
	{
		return a;
	}
	else if (b > a && b > c)
	{
		return b;
	}
	else
	{
		return c;
	}
}


template<typename T>
T Find_min(T a = 0, T b = 0, T c = 0)
{
	if (a < b && a < c)
	{
		return a;
	}
	else if (b < a && b < c)
	{
		return b;
	}
	else
	{
		return c;
	}
}

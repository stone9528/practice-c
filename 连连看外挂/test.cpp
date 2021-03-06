//隐藏程序运行时的黑框，防止截屏干扰
//#ifdef _MSC_VER
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
//#endif   
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <opencv2\imgproc\types_c.h>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

//游戏配置信息

//图片左上角坐标
#define left_x 13 
#define left_y 180
//图片长宽
#define pic_w 590
#define pic_h 386
//每个小方块长宽
#define block_x 31
#define block_y 35


using namespace cv;
using namespace std;

//截取屏幕图以及将其转换为Mat类型
void Screen();
BOOL HBitmapToMat(HBITMAP& _hBmp, Mat& _mat);
//图片切片
void picture_cut(Mat src);
//图片比较
double imgcompare(Mat img1, Mat img2);
//图片匹配，用到了广度优先搜索
void match();
void search_path(int i, int j, int m, int n, int search_flag[11][19], int dir, int temp);
HBITMAP	hBmp;
HBITMAP	hOld;

//将图片转化为数字矩阵，方便处理
int picture[11][19];
//统计每种图片有多少个（最多的即为空白部分）
int blank[300];
//搜索的标记及其方向
int bfsflag = 0;
int dirary[4][2] = { 1,0,-1,0,0,1,0,-1 };
int search_flag[11][19];
bool ifok = false;

int main()
{
	//int times = 3;
	//while (times--)
	//{
		HWND hq = FindWindow(NULL, "QQ游戏 - 连连看角色版");
		RECT rect;
		GetWindowRect(hq, &rect);
		int w = rect.right - rect.left, h = rect.bottom - rect.top;
		MoveWindow(hq, 0, 0, w, h, false);
		hq = FindWindow(NULL, "QQ游戏 - 连连看角色版");
		GetWindowRect(hq, &rect);
		Mat src;
		Screen();
		HBitmapToMat(hBmp, src);
		DeleteObject(hBmp);
		Mat imgROI = src(Rect(left_x, left_y, pic_w, pic_h));
		picture_cut(src);
		//进行1000次匹配，防止出错
		int temp = 500;
		while (temp--)
		{
			match();
		}
		//Sleep(3000);
		//int blank_num = 0;
		//如果这时检测到还有出了空白之外的图片，就用道具重置，继续完成上面步骤
		//for (int i = 0; i < 300; i++)
		//{
			//if (blank[i] != 0)
			//{
				//blank_num++;
			//}
		//}
		//if (blank_num == 0)
			//return 0;
		//else
		//{
			//::SetCursorPos(653, 199);
			//mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			//Sleep(1000);
		//}
	//}
	return 0;
}

void Screen()
{
	HDC hScreen = CreateDC("DISPLAY", NULL, NULL, NULL);
	HDC	hCompDC = CreateCompatibleDC(hScreen);
	int	nWidth = GetSystemMetrics(SM_CXSCREEN);
	int	nHeight = GetSystemMetrics(SM_CYSCREEN);
	hBmp = CreateCompatibleBitmap(hScreen, nWidth, nHeight);
	hOld = (HBITMAP)SelectObject(hCompDC, hBmp);
	BitBlt(hCompDC, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);
	SelectObject(hCompDC, hOld);
	DeleteDC(hScreen);
	DeleteDC(hCompDC);
}
BOOL HBitmapToMat(HBITMAP& _hBmp, Mat& _mat)
{
	BITMAP bmp;
	GetObject(_hBmp, sizeof(BITMAP), &bmp);
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	Mat v_mat;
	v_mat.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));
	GetBitmapBits(_hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, v_mat.data);
	_mat = v_mat;
	//imshow("图片", _mat);
	//waitKey(0);
	return TRUE;
}

void picture_cut(Mat src)
{
	//用vector储存每个小方块
	vector<vector<Mat>> vec;
	vec.resize(11);
	for (int i = 0; i < 11; i++)
	{
		vec[i].resize(19);
	}
	memset(blank, 0, sizeof(blank));//初始化数组
	vector<Mat> img;
	img.clear();
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			Mat pic = src(Rect(left_x+block_x*j, left_y+block_y*i, block_x, block_y));
			vec[i][j] = pic(Rect(1,1, 26, 29));
			if (img.empty())
			{
				img.push_back(vec[i][j]);
				picture[i][j] = 1;
				blank[0]++;
			}
			else
			{
				int flag = 0;
				for (int k = 0; k < img.size(); k++)
				{
					if (imgcompare(img[k], vec[i][j]) > 0.99)
					{
						picture[i][j] = k + 1;
						flag = 1;
						blank[k]++;
						break;
					}
				}//end for
				if (flag == 0)
				{
					img.push_back(vec[i][j]);
					picture[i][j] = img.size();
					blank[img.size() - 1]++;
				}//end if
			}//end else
		}//end for
	}//end for
	int pos = 0, num = 0;
	for (int i = 0; i < img.size(); i++)
	{
		if (blank[i] > num)
		{
			num = blank[i];
			pos = i + 1;
		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (picture[i][j] == pos)
				picture[i][j] = 0;
		}
	}
	//for (int ii = 0; ii < 11; ii++)
	//{
		//for (int jj = 0; jj < 19; jj++)
		//{
			//imshow("图片", vec[ii][jj]);
			//waitKey(0);
		//}
	//}

}

//直方图比较，结果为0到1的一个数，越大越准确
double imgcompare(Mat img1, Mat img2)
{
	Mat hsv_img1, hsv_img2;
	cvtColor(img1, hsv_img1, CV_BGR2HSV);
	cvtColor(img2, hsv_img2, CV_BGR2HSV);

	int h_bins = 50; int s_bins = 60;// 对hue通道使用30个bin,对saturatoin通道使用32个bin
	int histSize[] = { h_bins, s_bins };

	float h_ranges[] = { 0, 256 };// hue的取值范围从0到256, saturation取值范围从0到180
	float s_ranges[] = { 0, 180 };

	const float* ranges[] = { h_ranges, s_ranges };

	int channels[] = { 0, 1 };// 使用第0和第1通道

	MatND hist_test1;
	MatND hist_test2;

	calcHist(&hsv_img1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_img2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
	normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());


	double ans = compareHist(hist_test1, hist_test2, 0);
	return ans;
}

void match()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (picture[i][j] == 0)
				continue;
			for (int m = i; m < 11; m++)
			{
				for (int n = 0; n < 19; n++)
				{
					if (picture[m][n] == 0)
						continue;
					if (m == i && n == j)
						continue;
					if (picture[i][j] == picture[m][n])
					{
						memset(search_flag, 0, sizeof(search_flag));
						search_flag[i][j] = 1;
						bfsflag = 0;
						ifok = false;
						//用广度优先搜索检测两个相同的块能不能连通，能就true不能false
						search_path(i, j, m, n, search_flag, 0, 0);
						if (ifok)
						{
							//鼠标操作
							::SetCursorPos((left_x + j * block_x) + 10, (left_y + i * block_y) + 10);
							mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							//设置点击时间间隔为0到1秒的一个随机数（去掉即为瞬间连接）
							Sleep(100);
							::SetCursorPos((left_x + n * block_x) + 10, (left_y + m * block_y) + 10);
							mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							//blank[picturemap[i][j]] = blank[picturemap[i][j]] - 2;
							picture[i][j] = 0;
							picture[m][n] = 0;

						}

					}
				}
			}
		}
	}
}
void search_path(int i, int j, int m, int n, int search_flag[11][19], int dir, int temp)
{
	if (bfsflag == 1)
		return;
	if (temp > 2)
		return;
	if ((i == m) && (j == n))
	{
		bfsflag = 1;
		ifok = true;
		return;
	}
	for (int ii = 0; ii < 4; ii++)
	{
		int xx = i + dirary[ii][0];
		int yy = j + dirary[ii][1];
		if (xx < 0 || xx>10 || yy < 0 || yy >18 || search_flag[xx][yy] == 1)
			continue;
		search_flag[xx][yy] = 1;
		if ((picture[xx][yy] == 0) || (picture[xx][yy] == picture[m][n]))
		{
			if (dir == 0)
			{
				search_path(xx, yy, m, n, search_flag, ii + 1, temp);
			}
			else
			{
				if (ii + 1 != dir)
					search_path(xx, yy, m, n, search_flag, ii + 1, temp + 1);
				else
					search_path(xx, yy, m, n, search_flag, ii + 1, temp);
			}
			search_flag[xx][yy] = 0;
		}
	}
	return;
}
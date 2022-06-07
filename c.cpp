//
// Created by Honoka on 2021/5/9.
//

#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

BITMAPFILEHEADER FileHeader; //位图文件头

BITMAPINFOHEADER InfoHeader; //位图信息头

struct Pixel
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}; //像素结构体, 存储rgb值

Pixel p0;

//将小端法十六进制内存转为十进制
int LD2DEC(char* c, int len = 4)
{
	long l = 0;
	memcpy(&l, c, len);
	return (signed)l;
}

//限制函数
int clamp(int x, int a, int b)
{
	if (x <= a) return a;
	if (x >= b) return b;
	return x;
}

//把bmp信息写到文件
void writebmp(vector<Pixel> *p, int height, int width, int rowsize, ofstream& os)
{
	//构造文件头与信息头
	FileHeader.bfSize = sizeof(BITMAPFILEHEADER) + rowsize * height;
	InfoHeader.biWidth = width;
	InfoHeader.biHeight = height;


	cout << "New Size: " << FileHeader.bfSize << endl;
	cout << "New Rowsize: " << rowsize << endl;
	//输出文件头与信息头
	os.write(reinterpret_cast<char*>(&FileHeader), sizeof(BITMAPFILEHEADER));
	os.write(reinterpret_cast<char*>(&InfoHeader), sizeof(BITMAPINFOHEADER));

	for(int i = 0;i < abs(height); i++)
	{
		for(int j = 0;j < width; j++)
		{
			//cerr << i << " " << j << endl;
			if(j < p[i].size())
				os.write(reinterpret_cast<char*>(&p[i][j]),sizeof(Pixel));
			else
			{
				//输出空像素
				os.write(reinterpret_cast<char*>(&p0), sizeof(Pixel));
			}
		}
		//补齐四字节
		for(int j = 0;j < rowsize-3*width; j++)
		{
			os.write(reinterpret_cast<char*>(&p0.b),1);
		}
	}
}

//放大bmp
vector<Pixel>* zoom(vector<Pixel>* bmp, int height, int width, double bs, int& rowsize, int&nheight, int& nwidth)
{
	nheight = int(bs * height);
	nwidth = int(bs * width);
	vector<Pixel> * bmp2 = new vector<Pixel> [nheight];

	for(int i = 0;i < abs(nheight); i++)
	{
		for(int j = 0;j < nwidth;j++)
		{
			bmp2[i].push_back(bmp[clamp(int(double(i)/bs),0,height-1)][clamp(int(double(j)/bs),0,width-1)]);
		}
	}
	//新的rowsize
	rowsize = ((InfoHeader.biBitCount * nwidth + 31) / 32) * 4;
	return bmp2;
}
ifstream bmp;
ofstream bmpout;
int main(int argv, char **args)
{
	if(argv != 4)
	{
		cout << "?" << endl;
		return 0;
	}

	memset(&p0,0,sizeof p0);
	bmp.open(args[1], ios::binary | ios::in);
	bmpout.open(args[3], ios::out | ios::binary);
	int tbs;
	sscanf(args[2],"%d",&tbs);
	double bs = tbs/100.0;
	srand(time(NULL));
	if (bmp.is_open() && bmpout.is_open())
	{
		int rowsize, width, height, bitcount;
		cout << "!" << endl;
		bmp.read(reinterpret_cast<char*>(&FileHeader), sizeof(BITMAPFILEHEADER));
		cout << "Offset: " << LD2DEC(reinterpret_cast<char*>(&FileHeader.bfOffBits)) << endl;
		cout << "File Size: " << LD2DEC(reinterpret_cast<char*>(&FileHeader.bfSize)) << endl;
		bmp.read(reinterpret_cast<char*>(&InfoHeader), sizeof(BITMAPINFOHEADER));
		cout << "Height: " << (height = LD2DEC(reinterpret_cast<char*>(&InfoHeader.biHeight))) << endl;
		cout << "Width: " << (width = LD2DEC(reinterpret_cast<char*>(&InfoHeader.biWidth))) << endl;
		cout << "Bit Count: " << (bitcount = LD2DEC(reinterpret_cast<char*>(&InfoHeader.biBitCount))) << endl;
		cout << "Row Size: " << (rowsize = ((InfoHeader.biBitCount * InfoHeader.biWidth + 31) / 32) * 4) << endl;


		auto *p = new vector <Pixel> [abs(height)];
		//读入bmp
		for (int i = 0; i < abs(height); i++)
		{
			for (int j = 0; j < width; j++)
			{
				Pixel t;
				bmp.read(reinterpret_cast<char*>(&t),sizeof(Pixel));
				p[i].push_back(t);
			}
			bmp.ignore(rowsize - 3*width); //跳过补齐字节
		}
		int orowsize, nheight, nwidth;
		auto outb = zoom(p,height,width,bs,orowsize,nheight,nwidth);
		writebmp(outb, nheight, nwidth, orowsize, bmpout);
	}
	else
	{
		cout << "?" << endl;
	}
	return 0;
}
//
// Created by Honoka on 2021/5/10.
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
const int MAX_COMP_LENGTH = 127;
const int TRUNK_SIZE = 10 * 1024 * 1024;

//压缩字节
vector<unsigned char> ys(vector<unsigned char>& buf)
{

	auto bufo = vector<unsigned char>();
	int tip = 0;
	while(true)
	{
		if(tip == buf.size()) break;
		int ttip = tip;
		int ctip = 0;
		bufo.push_back(0);
		bool ok = false;
		while(tip+1 < buf.size() && buf[tip] == buf[tip+1] && tip-ttip+1 < MAX_COMP_LENGTH)
		{
			if(!ok)
			{
				bufo.push_back(buf[tip]);
				ctip++;
			}
			ok = true;
			tip ++;
		}
		if(tip == ttip)
		{
			while(tip+1 < buf.size() && buf[tip] != buf[tip+1] && (tip+2 >= buf.size() || buf[tip+1] != buf[tip+2]) && tip-ttip+1 < MAX_COMP_LENGTH)
			{
				bufo.push_back(buf[tip]);
				ctip++;
				tip ++;
			}
		}
		//cout << bufo.size()-1-(tip-ttip)<< endl;
		if(ok) //repeat
		{
			bufo[bufo.size()-1-ctip] = (1 << 7) + tip-ttip+1;
		}else{
			bufo[bufo.size()-1-ctip] = tip-ttip+1;
		}
		if(!ok)
			bufo.push_back(buf[tip]);
		tip++;
	}
	return bufo;
}

//读入下一个字节, 处理分块等问题
bool getnxtbyte(ifstream& ins, unsigned char &ch)
{
	static vector<unsigned char> buf;
	static int tip = 0;
	static int ttip = 0;
	if(tip >= buf.size())
	{
		cout << (ttip++) * TRUNK_SIZE << "Bytes" << endl;
		buf.clear();
		tip = 0;
		int cnt = 0;
		while (cnt < TRUNK_SIZE && ins.read(reinterpret_cast<char*>(&ch), 1)) buf.push_back(ch), cnt++;
		if(cnt == 0) return false;
	}
	ch = buf[tip++];
	return true;
}

//解压字节
void jy(ifstream& ins, ofstream& ous)
{
	int tip = 0;
	unsigned char ch;
	while(getnxtbyte(ins, ch))
	{
		if(((1 << 7) & ch) > 0)
		{
			ch -= (1 << 7);
			unsigned char tch;
			getnxtbyte(ins,tch);
			for(int i = 0;i < (int)ch; i++)
			{
				ous << tch;
			}
		}else{
			for(int i = 1;i <= (int)ch; i++)
			{
				unsigned char tch;
				getnxtbyte(ins,tch);
				ous << tch;
			}
		}
	}
	ous.flush();
	return ;
}

//对文件进行压缩
void compress(ifstream &ins, ofstream& ous)
{
	int tcnt = 0;
	while(true)
	{
		cout << (tcnt++) * TRUNK_SIZE << "Bytes" << endl;
		vector<unsigned char> indata;
		unsigned char ch;
		int cnt = 0;
		while (cnt < TRUNK_SIZE && ins.read(reinterpret_cast<char*>(&ch), 1)) indata.push_back(ch), cnt++;

		auto rle = ys(indata);
		for (auto& c : rle)
		{
			ous << c;
		}
		ous.flush();
		if(cnt < TRUNK_SIZE) break;
	}
}
int main(int argv, char **args)
{
	if(argv != 4)
	{
		cout << "爬" << endl;
		return 0;
	}
	if(strcmp(args[2],"-d") == 0)
	{
		ifstream ins;
		ins.open(args[1], ios::in | ios::binary);
		ofstream ous;
		ous.open(args[3], ios::out | ios::binary);
		jy(ins,ous);
		cout << "...Done!" << endl;
	}else if(strcmp(args[2],"-c") == 0)
	{
		ifstream ins;
		ins.open(args[1], ios::in | ios::binary);
		ofstream ous;
		ous.open(args[3], ios::out | ios::binary);
		compress(ins,ous);
		cout << "...Done!" << endl;
	}else{
		cout << "爬" << endl;
		return 0;
	}
	return 0;
}

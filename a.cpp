#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#define MAXN 1005
using namespace std;
struct BigNumber{
	int d[MAXN],len;
	int flag = 1;//正负号
	BigNumber(){len=1;memset(d,0,sizeof d);} //构造函数
	void clean()
	{
		while(len > 1 && d[len-1] == 0)len--;
		if(len == 1 && d[len-1] == 0) flag = 1; //避免出现-0
	}
	BigNumber operator = (const char * num)
	{
		//负数
		if(num[0] == '-')
		{
			flag = -1;
			num++;
		}
		memset(d,0,sizeof d);
		len = strlen(num);
		for(int i = 0;i < len;i++)
		{
			d[i] = num[len-i-1]-'0';
		}
		clean();
		return *this;
	}
	BigNumber operator = (int num)
	{
		char s[20];
		sprintf(s,"%d",num);
		*this = s;
		return *this;
	}
	BigNumber qf()
	{
		BigNumber c = *this;
		c.flag *= -1;
		return c;
	}
	BigNumber operator + (BigNumber b)
	{
		if(this->flag == -1 && b.flag == -1)
		{
			return (this->qf() + b.qf()).qf();
		}
		if(this->flag == -1 && b.flag == 1)
		{
			return (b - this->qf());
		}
		if(this->flag == 1 && b.flag == -1)
		{
			return *this - b.qf();
		}
		BigNumber c = *this;int i;
		for(i = 0;i < b.len;i++)
		{
			c.d[i] += b.d[i];
			if(c.d[i] >= 10)c.d[i]%=10,c.d[i+1]++; //进位
		}
		while(c.d[i] >= 10)c.d[i]%=10,c.d[i+1]++,i++; //进位
		c.len = max(len,b.len)+1;
		c.clean();
		return c;
	}
	//a>b 返回1
	int cmp(BigNumber a, BigNumber b)
	{
		if(a.flag == -1 && b.flag == 1)
			 return -1;
		if(a.flag == 1 && b.flag == -1)
			return 1;
		if(a.len != b.len)
		{
			if (a.len > b.len)
				return a.flag;
			return -1 * a.flag;
		}
		for(int i = a.len-1;i >= 0;i--)
		{
			if(a.d[i] > b.d[i])
			{
				return a.flag;
			}else if(a.d[i] < b.d[i])
			{
				return -1 * a.flag;
			}
		}
		return 1;
	}
	BigNumber operator - (BigNumber b)
	{
		if(this->flag == -1 && b.flag == -1)
		{
			return b.qf()-(*this).qf();
		}
		if(this->flag == -1 && b.flag == 1)
		{
			return (this->qf() + b).qf();
		}
		if(this->flag == 1 && b.flag == -1)
		{
			return *this + b.qf();
		}
		if(cmp(*this,b) == -1)
		{
			return (b-*this).qf();
		}
		BigNumber c = *this;int i;
		for(i = 0;i < b.len;i++)
		{
			c.d[i] -= b.d[i];
			if(c.d[i] < 0)c.d[i]+=10,c.d[i+1]--; //借位
		}
		while(c.d[i] < 0)c.d[i]+=10,c.d[i+1]--,i++; //借位
		c.len = max(len,b.len)+1;
		c.clean();
		return c;
	}
	string str()
	{
		char c[MAXN]={};
		int offs = 0;
		if(flag == -1) //输出符号
		{
			c[0] = '-';
			offs = 1;
		}
		for(int i = 0;i < len;i++)
		{
			c[i + offs] = d[len-1-i] + '0';
		}
		return c;
	}
};
char ca[2005],cb[2005];
int main()
{
	while(true)
	{
		BigNumber a, b;
		cin >> ca >> cb;
		a = ca;
		b = cb;
		cout << (a + b).str() << endl;
		cout << (a - b).str() << endl;
	}
}

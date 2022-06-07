//
// Created by Honoka on 2021/5/8.
//

#include <iostream>
#include <cstdio>

using namespace std;

//链表节点结构体
struct StackNode
{
	int val; //数据
	StackNode* pre, * nxt; //前驱 后继
};

//封装后的栈
struct Stack
{

	StackNode* head; //链表头节点
	StackNode* top; //栈顶节点
	int size; //栈大小
	Stack() //构造函数
	{
		head = (StackNode*)malloc(sizeof(StackNode));
		head->nxt = head->pre = nullptr;
		top = head;
		size = 0;
	}

	int gettop() const
	{
		if (top == head) //栈为空
		{
			return 0;
		}
		return top->val;
	}

	void push(int x)
	{
		auto* t = (StackNode*)malloc(sizeof(StackNode));
		//链表尾添加节点
		top->nxt = t;
		t->pre = top;
		t->nxt = nullptr;
		t->val = x;
		top = t;
		size++;
		return;
	}

	void pop()
	{
		if (head == top) return; //栈为空
		auto t = top;
		top = top->pre;
		top->nxt = nullptr;
		size--;
		free(t); //释放内存
		return;
	}

};

int main()
{
	Stack s;
	for (int i = 0; i <= 10; i++)
	{
		s.push(2 * i + 1);
	}
	while (s.size != 0)
	{
		cout << s.gettop() << endl;
		s.pop();
	}
	return 0;
}
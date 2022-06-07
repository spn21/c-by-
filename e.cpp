//
// Created by Honoka on 2021/5/11.
//

#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <vector>
#define INF 0x3f3f3f3f
using namespace std;

struct Book
{
	string name;
	int id;
	Book* nxt;
	int rentid; //借这本书的用户id
};

struct User
{
	string name;
	int id;
	User* nxt;
};

User* headuser;
Book* headbook;

//添加用户
void adduser(int id, string name)
{
	auto nown = headuser;
	while(nown->nxt != nullptr && nown->nxt->id < id)
	{
		nown = nown->nxt;
	}
	auto newn = new User;
	newn->nxt = nown->nxt;
	nown->nxt = newn;
	newn->id = id;
	newn->name = name;
	return ;
}

//添加书
void addbook(int id, string name, int rentid)
{
	auto nown = headbook;
	while(nown->nxt != nullptr && nown->nxt->id <= id)
	{
		nown = nown->nxt;
	}
	auto newn = new Book;
	newn->nxt = nown->nxt;
	nown->nxt = newn;
	newn->id = id;
	newn->rentid = rentid;
	newn->name = name;
	return ;
}

//输出所有用户
void printUsers()
{
	auto nown = headuser;
	printf("id  name\n");
	while(nown->nxt != nullptr)
	{
		printf("%3d %s\n", nown->nxt->id, nown->nxt->name.c_str());
		nown = nown->nxt;
	}
	printf("\n");
	return ;
}

//输出所有书籍
void printBooks()
{
	auto nown = headbook;
	printf("id  name\n");
	int cnt = 0;
	while(nown->nxt != nullptr)
	{
		if(nown->id != -1 && nown->id != nown->nxt->id)
		{
			printf("%3d %s %3d\n", nown->id, nown->name.c_str(), cnt);
			cnt = 0;
		}
		nown = nown->nxt;
		cnt ++;
	}
	if(nown->id != -1)
	{
		printf("%3d %s %3d\n", nown->id, nown->name.c_str(), cnt);
	}
	printf("\n");
	return ;
}

//删除一个用户
void deluser(int id)
{
	auto nown = headuser;
	while(nown->nxt != nullptr && nown->nxt->id != id)
	{
		nown = nown->nxt;
	}

	printf("Deleted %s!\n",nown->nxt->name.c_str());
	fflush(stdout);
	auto t = nown->nxt;
	nown->nxt = t->nxt;
	free(t);
	return ;
}

//删除书
int delbook(int id, int cnt)
{
	auto nown = headbook;
	int tcnt = 0;
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->id == id && nown->nxt->rentid == -1)
		{
			auto t = nown->nxt;
			nown->nxt = t->nxt;
			free(t);
			tcnt++;
			if(tcnt == cnt) //删够了
			{
				break;
			}
		}else{
			nown = nown->nxt;
		}

	}

	printf("Deleted %d Books!\n", tcnt);
	fflush(stdout);
	return tcnt;
}

//改一本书的名字
void changebookname(int id, string name)
{
	auto nown = headbook;
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->id == id)
		{
			nown->nxt->name = name;
		}
		nown = nown->nxt;
	}
	return ;
}

//改一个用户的名字
void changeusername(int id, string name)
{
	auto nown = headuser;
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->id == id)
		{
			nown->nxt->name = name;
		}
		nown = nown->nxt;
	}
	return ;
}

//还书
void returnBooks(int userid, int bookid)
{
	auto nown = headbook;
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->id == bookid && nown->nxt->rentid == userid)
		{
			nown->nxt->rentid = -1;
		}
		nown = nown->nxt;
	}

}

//借书
void rentBooks(int userid, int bookid)
{
	auto nown = headbook;
	bool ok = false;
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->id == bookid && nown->nxt->rentid == -1)
		{
			nown->nxt->rentid = userid;
			ok = true;
			break;
		}
		nown = nown->nxt;
	}
	if(!ok)
	{
		printf("Out of Books!\n");
	}
	return ;
}

//查询一本书有谁借了
void findUserByBooks(int bookid)
{
	auto nown = headbook;
	printf("Books %d are rent by: \n", bookid);
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->id == bookid && nown->nxt->rentid != -1)
		{
			printf("User %d\n", nown->nxt->rentid);
		}
		nown = nown->nxt;
	}
	return ;
}

//查一个人借了哪些书
void findBooksbyUser(int userid)
{
	auto nown = headbook;
	printf("User %d has rent: \n", userid);
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->rentid == userid)
		{
			printf("Book %d, %s\n", nown->nxt->id, nown->nxt->name.c_str());
		}
		nown = nown->nxt;
	}
}

//保存用户
void saveUsers()
{
	FILE *fp = fopen("users.txt","w");
	auto nown = headuser;
	while(nown->nxt != nullptr)
	{
		fprintf(fp,"%3d %s\n", nown->nxt->id, nown->nxt->name.c_str());
		nown = nown->nxt;
	}
	fprintf(fp,"\n");
	fclose(fp);
	return ;
}

//保存书
void saveBooks()
{
	FILE *fp = fopen("books.txt","w");
	auto nown = headbook;
	while(nown->nxt != nullptr)
	{
		fprintf(fp,"%3d %s %d\n", nown->nxt->id, nown->nxt->name.c_str(), nown->nxt->rentid);
		nown = nown->nxt;
	}
	printf("\n");
	fclose(fp);
	return ;
}

//读取用户
void readUsers()
{
	FILE *fp = fopen("users.txt","r");
	char buf[200];
	int tid;
	while(~fscanf(fp,"%d %s", &tid, buf))
	{
		adduser(tid,string(buf));
	}
	fclose(fp);
	return ;
}

//读取书
void readBooks()
{
	FILE *fp = fopen("books.txt","r");
	char buf[200];
	int tid, trentid;
	while(~fscanf(fp,"%d %s %d", &tid, buf,&trentid))
	{
		addbook(tid,string(buf),trentid);
	}
	fclose(fp);
	return ;
}

char buf[200];

//管理界面
void printadminmenu()
{

	while(true)
	{
		printf("========== Main Menu ==========\n");
		printf("1. Books Management\n");
		printf("2. Users Management\n");
		printf("3. Info\n");
		printf("4. Save\n");
		printf("5. Open\n");
		printf("6. Exit\n");
		fflush(stdout);
		int k;
		scanf("%d", &k);
		if (k == 1)
		{
			printf("========== Book Management ==========\n");
			printBooks();
			printf("1. Add Books\n");
			printf("2. Modify Books\n");
			printf("3. Delete Books\n");
			fflush(stdout);

			int tk;
			scanf("%d", &tk);
			if (tk == 1)
			{
				int cnt, id;
				printf("Input the id, name and the quantity.\n");
				fflush(stdout);
				scanf("%d%s%d", &id, buf, &cnt);
				for (int i = 1; i <= cnt; i++)
					addbook(id, string(buf),-1);
			}
			else if (tk == 2)
			{
				int tid;
				printf("Input the id:\n");
				fflush(stdout);
				scanf("%d", &tid);
				printf("Input the name you want to change to:\n");
				fflush(stdout);
				scanf("%s", buf);
				changebookname(tid, buf);
			}
			else if (tk == 3)
			{
				int tid, tcnt;
				printf("Input the id:\n");
				fflush(stdout);
				scanf("%d", &tid);
				printf("Input the quantity you want to delete:\n");
				fflush(stdout);
				scanf("%d", &tcnt);
				delbook(tid, tcnt);
			}
		}else if(k == 2)
		{
			printf("========== User Management ==========\n");
			printUsers();
			printf("1. Add Users\n");
			printf("2. Modify Users\n");
			printf("3. Delete Users\n");
			fflush(stdout);

			int tk;
			scanf("%d", &tk);
			if (tk == 1)
			{
				int id;
				printf("Input the id and name: \n");
				fflush(stdout);
				scanf("%d%s", &id, buf);
				adduser(id, string(buf));
			}
			else if (tk == 2)
			{
				printf("========== Modify Users ==========\n");
				printf("1. Change name\n");
				printf("2. Rend\n");
				printf("3. Return\n");
				int ttk;
				scanf("%d",&ttk);
				if(ttk == 1)
				{
					int tid;
					printf("Input the id:\n");
					fflush(stdout);
					scanf("%d", &tid);
					printf("Input the name you want to change to:\n");
					fflush(stdout);
					scanf("%s", buf);
					changeusername(tid, buf);
				}else if(ttk == 2)
				{
					printf("Input the render id and the book id:\n");
					fflush(stdout);
					int tid, tbookid;
					scanf("%d %d",&tid, &tbookid);
					rentBooks(tid, tbookid);
				}else if(ttk == 3)
				{
					printf("Input the render id and the book id:\n");
					fflush(stdout);
					int tid, tbookid;
					scanf("%d %d",&tid, &tbookid);
					returnBooks(tid, tbookid);
				}
			}
			else if (tk == 3)
			{
				int tid;
				printf("Input the id:\n");
				fflush(stdout);
				scanf("%d", &tid);
				deluser(tid);
			}
		}else if(k == 3)
		{
			printf("========== Info ==========\n");
			printf("1. Books rent by a User.\n");
			printf("2. Users who rent a Book.\n");
			int tk;
			scanf("%d",&tk);
			if(tk == 1)
			{
				int tid;
				printf("Input the User id:\n");
				fflush(stdout);
				scanf("%d", &tid);
				findBooksbyUser(tid);
			}else if(tk == 2)
			{
				int tid;
				printf("Input the Book id:\n");
				fflush(stdout);
				scanf("%d", &tid);
				findUserByBooks(tid);
			}
		}else if(k == 4)
		{
			saveBooks();
			saveUsers();
		}else if(k == 5)
		{
			readBooks();
			readUsers();
		}else if(k == 6)
		{
			return ;
		}

	}
}

//用户界面
int findUser(string name)
{
	auto nown = headuser;
	while(nown->nxt != nullptr)
	{
		if(nown->nxt->name == name) return nown->nxt->id;
		nown = nown->nxt;
	}
	printf("\n");
	return -1;
}
void printusermenu(string name)
{

	readUsers();
	readBooks();
	int tid = findUser(name);
	if(tid == -1)
	{
		printf("User not found!\n");
		return ;
	}
	while(true)
	{
		printf("========== Main Menu ==========\n");
		printf("1. Rend\n");
		printf("2. Return\n");
		printf("3. Info\n");
		printf("4. Save & Exit\n");
		int tk;
		scanf("%d", &tk);
		if (tk == 1)
		{
			printf("Input the book id: \n");
			int bid;
			scanf("%d", &bid);
			rentBooks(tid, bid);
		}
		else if (tk == 2)
		{
			printf("Input the book id: \n");
			int bid;
			scanf("%d", &bid);
			returnBooks(tid, bid);
		}
		else if (tk == 3)
		{
			findBooksbyUser(tid);
		}else if(tk == 4)
		{
			saveUsers();
			saveBooks();
			return ;
		}
	}
	return ;
}

int main(int argv, char** args)
{
	headbook = new Book;
	headuser = new User;
	headbook->nxt = nullptr;
	headuser->nxt = nullptr;
	headbook->id = headuser->id = -1;



	if(strcmp(args[1],"-a") == 0)
	{
		printadminmenu();
	}else if(strcmp(args[1],"-u") == 0)
	{
		printusermenu(string(args[2]));
	}
	return 0;
}

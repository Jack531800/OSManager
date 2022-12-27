#include "CatalogManager.h"

bool IsInMaster(dirNode* p);
void Write_File(dirNode* p);
void Read_File(dirNode* p);
void Transfer_In_File(dirNode* p);
void Transfer_Out_File(dirNode* p);
void Create_File(dirNode* p);
void Delete_File(dirNode* p);

void mkdir(char dirName[]) {
	int flag;
	dirNode* p, * q;
	q = new dirNode;
	strcpy_s(q->name, dirName);
	q->sub = NULL;
	q->type = 0;
	q->next = NULL;
	q->father = workDir;
	q->size = 0;
	q->str = NULL;
	p = workDir->sub;
	if (p == NULL)
	{
		workDir->sub = q;
		cout << "\"" << dirName << "子目录创建成功" << endl;
	}
	else
	{
		flag = 0;
		while (p)
		{
			if (p->type == 0)
			{
				if (!strcmp(p->name, dirName))
				{
					flag = 1;
					break;
					cout << "错误，\"" << dirName << "\"子目录已存在" << endl;
				}
			}
			p = p->next;
		}
		if (flag == 0)
		{
			p = workDir->sub;
			while (p->next)
			{
				p = p->next;
			}
			p->next = q;
			cout << "\"" << dirName << "子目录创建成功" << endl;
		}
	}
}

void rmdir(char dirName[]) {
	dirNode* p, * q;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
	{
		cout << "错误，\"" << dirName << "\"子目录已存在" << endl;
	}
	else
	{
		while (p)
		{
			if (p->type == 0)
			{
				if (!strcmp(p->name, dirName))
				{
					flag = 1;
					break;
				}
			}
			p = p->next;
		}
		if (flag == 1)
		{
			if (p->sub)
				cout << "错误，\"" << dirName << "\"子目录下存在子目录或文件" << endl;
			else
			{
				if (p == workDir->sub)
					workDir->sub = p->next;
				else
				{
					q = workDir->sub;
					while (q->next != p)
						q = q->next;
					q->next = p->next;
					delete p;
				}
				cout << "\"" << dirName << "子目录已删除" << endl;
			}
		}
		else
			cout << "错误，\"" << dirName << "\"子目录不存在" << endl;
	}
}

void create_dentry(char fileName[]) {
	int flag;
	dirNode* p, * q;
	q = new dirNode;
	strcpy_s(q->name, fileName);
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&q->t, &now);  //获取当地日期和时间
	unsigned long size = 255;
	GetComputerName(q->PCName, &size);//GetComputerName()函数的第一个参数的类型是LPWSTR，所以直接使用wchar定义前面的数组
	GetUserName(q->UserName, &size);//GetUserName()函数同上
	//printf("The computer's name is :%S\n", PCName);//打印要用%S，对应wchar		
	//printf("The computer's user name is %S\n", UserName);
	//system("pause");
	q->sub = NULL;
	q->type = 1;
	q->next = NULL;
	q->father = workDir;
	q->str = (char*)malloc(50 * sizeof(char));
	q->size = 0;
	p = workDir->sub;
	if (p == NULL)
	{
		workDir->sub = q;
		cout << "\"" << fileName << "文件创建成功" << endl;
		Create_File(p);
	}
	else
	{
		flag = 0;
		while (p)
		{
			if (p->type == 1)
			{
				if (!strcmp(p->name, fileName))
				{
					flag = 1;
					break;
					cout << "错误，\"" << fileName << "\"文件已存在" << endl;
				}
			}
			p = p->next;
		}
		if (flag == 0)
		{
			p = workDir->sub;
			while (p->next)
			{
				p = p->next;
			}
			p->next = q;
			cout << "\"" << fileName << "文件创建成功" << endl;
			Create_File(p);
		}
	}
}

void rmfile(char fileName[]) {
	dirNode* p, * q;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
		cout << "错误，\"" << fileName << "\"文件不存在" << endl;
	else
	{
		while (p)
		{
			if (p->type == 1)
			{
				if (!strcmp(p->name, fileName))
				{
					flag = 1;
					break;
				}
			}
			p = p->next;
		}
		if (flag == 1)
		{
			if (IsInMaster(p))
				cout << "错误\"" << fileName << "\"已装入内存" << endl;
			else
			{
				if (p == workDir->sub)
					workDir->sub = p->next;
				else
				{
					q = workDir->sub;
					while (q->next != p)
						q = q->next;
					q->next = p->next;
					Delete_File(p);
					delete p;
				}
				cout << "\"" << fileName << "文件已删除" << endl;
			}
		}
		else
			cout << "错误，\"" << fileName << "\"文件不存在" << endl;

	}
}

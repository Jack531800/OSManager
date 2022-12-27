//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_CATALOGMANAGER_H
#define OSMANAGER_CATALOGMANAGER_H


#include<iostream>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<cstdlib>
#include<Windows.h>
using namespace std;
#define  _WINSOCK_DEPRECATED_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

typedef class CatalogManager {
public:
    //构造函数根据自身情况添加参数
    CatalogManager(DiskManager *disk_manager);
    
    ~CatalogManager() = default;


    //新建目录
    void mkdir(std::char dirName[]);

    //删除目录
    void rmdir(std::char dirName[]);

    //为文件建立目录项
    void create_dentry(std::char fileName[]);

    //删除文件
    void rmfile(std::char fileName[]);

    bool IsInMaster(dirNode* p);
    
    void Write_File(dirNode* p);
    void Read_File(dirNode* p);
    void Transfer_In_File(dirNode* p);
    void Transfer_Out_File(dirNode* p);
    void Create_File(dirNode* p);
    void Delete_File(dirNode* p);
private:
    //用上的数据结构都放这
    char name[50];
	int type;
	struct tm t;
	CatalogManager* next;
	CatalogManager* sub;
	CatalogManager* father;
	int size;
	char* str;
	int addr;
	WCHAR PCName[255];//直接使用wchar类型定义
	WCHAR UserName[255];
}dirNode;
dirNode* workDir;
dirNode root;
char path[100];


#endif //OSMANAGER_CATALOGMANAGER_H

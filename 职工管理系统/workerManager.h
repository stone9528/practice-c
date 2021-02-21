#pragma once
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();

	int empNum;//员工总数
	Worker** empArray;//员工数组
	bool fileIsEmpty;//文件是否存在

	void showMenu();//菜单显示
	void addEmplyee();//增加员工
	void save();//将职工信息保存到文件中
	int getEmpNum();//统计文件中职工人数
	void initEmp();//初始化职工信息
	void showEmp();//显示职工信息
	void deleteEmp();//删除职工
	int empIsExist(int id);//判断职工是否存在
	void editEmp();//修改职工信息
	void findEmp();//查找职工
	void sortEmp();//对员工排序
	void emptyFile();//清空文件
	void exitSystem();//退出菜单

	~WorkerManager();
};
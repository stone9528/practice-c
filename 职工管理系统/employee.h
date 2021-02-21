//普通职工类
#pragma once
#include"worker.h"

class Employee:public Worker
{
public:
	Employee(int id,string name,int deptId);

	virtual void showInfo();//显示职工详细信息
	virtual string getDeptName();//获取职工部门名称
};
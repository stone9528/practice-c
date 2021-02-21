//职工类
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
	int id;//职工编号
	string name;//职工姓名
	int deptId;//部门编号

	virtual void showInfo() = 0;//显示职工信息
	virtual string getDeptName() = 0;//获取获取部门名称
};
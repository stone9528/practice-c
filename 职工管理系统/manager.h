//æ≠¿Ì¿‡
#pragma once
#include"worker.h"
using namespace std;

class Manager:public Worker
{
public:
	Manager(int id,string name,int deptId);

	virtual void showInfo();
	virtual string getDeptName();
};
//��ְͨ����
#pragma once
#include"worker.h"

class Employee:public Worker
{
public:
	Employee(int id,string name,int deptId);

	virtual void showInfo();//��ʾְ����ϸ��Ϣ
	virtual string getDeptName();//��ȡְ����������
};
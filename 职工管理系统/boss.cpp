#include"boss.h"

Boss::Boss(int id, string name, int deptId)
{
	this->id = id;
	this->name = name;
	this->deptId = deptId;
}

void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->id << "\tְ��������" << this->name
		<< "\tְ�����ţ�" << this->getDeptName()
		<< "\t��λְ�𣺹���˾��������" << endl;
}

string Boss::getDeptName()
{
	return string("�ϰ�");
}
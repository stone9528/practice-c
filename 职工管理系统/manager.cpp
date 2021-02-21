#include"manager.h"

Manager::Manager(int id, string name, int deptId)
{
	this->id = id;
	this->name = name;
	this->deptId = deptId;
}

void Manager::showInfo()
{
	cout << "职工编号：" << this->id << "\t职工姓名：" << this->name
		<< "\t职工部门：" << this->getDeptName()
		<< "\t岗位职责：听从老板发布的任务，并下发给普通员工" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}
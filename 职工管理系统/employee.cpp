#include"employee.h"

Employee::Employee(int id, string name, int deptId)
{
	this->id = id;
	this->name = name;
	this->deptId = deptId;
}

void Employee::showInfo()
{
	cout << "职工编号：" << this->id << "\t职工姓名：" << this->name 
		<< "\t职工部门：" << this->getDeptName() 
		<<"\t岗位职责：完成经理分配的任务"<< endl;
}

string Employee::getDeptName()
{
	return string("普通员工");
}
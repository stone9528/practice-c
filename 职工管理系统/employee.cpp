#include"employee.h"

Employee::Employee(int id, string name, int deptId)
{
	this->id = id;
	this->name = name;
	this->deptId = deptId;
}

void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->id << "\tְ��������" << this->name 
		<< "\tְ�����ţ�" << this->getDeptName() 
		<<"\t��λְ����ɾ�����������"<< endl;
}

string Employee::getDeptName()
{
	return string("��ͨԱ��");
}
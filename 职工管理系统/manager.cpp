#include"manager.h"

Manager::Manager(int id, string name, int deptId)
{
	this->id = id;
	this->name = name;
	this->deptId = deptId;
}

void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->id << "\tְ��������" << this->name
		<< "\tְ�����ţ�" << this->getDeptName()
		<< "\t��λְ�������ϰ巢�������񣬲��·�����ͨԱ��" << endl;
}

string Manager::getDeptName()
{
	return string("����");
}
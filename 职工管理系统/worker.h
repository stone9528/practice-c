//ְ����
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
	int id;//ְ�����
	string name;//ְ������
	int deptId;//���ű��

	virtual void showInfo() = 0;//��ʾְ����Ϣ
	virtual string getDeptName() = 0;//��ȡ��ȡ��������
};
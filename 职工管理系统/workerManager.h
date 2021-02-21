#pragma once
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();

	int empNum;//Ա������
	Worker** empArray;//Ա������
	bool fileIsEmpty;//�ļ��Ƿ����

	void showMenu();//�˵���ʾ
	void addEmplyee();//����Ա��
	void save();//��ְ����Ϣ���浽�ļ���
	int getEmpNum();//ͳ���ļ���ְ������
	void initEmp();//��ʼ��ְ����Ϣ
	void showEmp();//��ʾְ����Ϣ
	void deleteEmp();//ɾ��ְ��
	int empIsExist(int id);//�ж�ְ���Ƿ����
	void editEmp();//�޸�ְ����Ϣ
	void findEmp();//����ְ��
	void sortEmp();//��Ա������
	void emptyFile();//����ļ�
	void exitSystem();//�˳��˵�

	~WorkerManager();
};
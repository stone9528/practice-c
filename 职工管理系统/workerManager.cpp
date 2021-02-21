#include"workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs(FILENAME, ios::in);

	//�ļ�������
	if (!ifs.is_open())
	{
		this->empNum = 0;
		this->empArray = NULL;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڵ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->empNum = 0;
		this->empArray = NULL;
		this->fileIsEmpty = true;
		ifs.close();
	}

	//�ļ����������ݲ�Ϊ��
	int size = this->getEmpNum();
	this->empNum = size;
	this->empArray = new Worker*[size];
	this->fileIsEmpty = false;
	this->initEmp();
}

//�˵���ʾ
void WorkerManager::showMenu()
{
	cout << "************************************" << endl;
	cout << "******* ��ӭʹ��ְ������ϵͳ *******" << endl;
	cout << "********** 0.�˳�������� **********" << endl;
	cout << "********** 1.����ְ����Ϣ **********" << endl;
	cout << "********** 2.��ʾְ����Ϣ **********" << endl;
	cout << "********** 3.ɾ����ְְ�� **********" << endl;
	cout << "********** 4.�޸�ְ����Ϣ **********" << endl;
	cout << "********** 5.����ְ����Ϣ **********" << endl;
	cout << "********** 6.���ձ������ **********" << endl;
	cout << "********** 7.��������ĵ� **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//����Ա��
void WorkerManager::addEmplyee()
{
	int newEmpNum = 0;//��Ա����
	cout << "������Ҫ������Ա������" << endl;
	cin >> newEmpNum;

	if (newEmpNum > 0)
	{
		int newSize = newEmpNum + this->empNum;//�µ�Ա������
		Worker** newSpace = new Worker*[newSize];//�µĴ�ſռ�

		//ת��֮ǰ�����ݵ��¿ռ�
		for (int i = 0; i < this->empNum; i++)
		{
			newSpace[i] = this->empArray[i];
		}

		int id;//��Ա���ı��
		string name;//��Ա��������
		int deptId;//��Ա���Ĳ��ű��
		//������Ա����Ϣ
		for (int i = 0; i < newEmpNum; i++)
		{
			cout << "�������" << i + 1 << "����Ա���ı�ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����Ա�������֣�" << endl;
			cin >> name;
			cout << "��ѡ���" << i + 1 << "����Ա���Ĳ��ţ�" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> deptId;

			Worker* worker = NULL;
			switch (deptId)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			newSpace[this->empNum + i] = worker;
		}

		//�ͷ�֮ǰ�Ŀռ�
		delete[] this->empArray;

		//���µ�ַ�ռ�
		this->empArray = newSpace;

		//����ְ������
		this->empNum = newSize;

		//�����ļ����ڱ�־
		if (this->fileIsEmpty)
		{
			this->fileIsEmpty = false;
		}

		cout << "�ɹ�����" << newEmpNum << "����Ա��" << endl;

		//���浽�ļ���
		this->save();
	}
	else
	{
		cout << "��������ִ���" << endl;
	}

	system("pause");
	system("cls");
}

//��ְ����Ϣ���浽�ļ���
void WorkerManager::save()
{
	ofstream ofs(FILENAME, ios::out);

	for (int i = 0; i < this->empNum; i++)
	{
		ofs << this->empArray[i]->id << " "
			<< this->empArray[i]->name << " "
			<< this->empArray[i]->deptId << endl;
	}

	ofs.close();
}

//ͳ���ļ���ְ������
int WorkerManager::getEmpNum()
{
	ifstream ifs(FILENAME, ios::in);

	int id;
	string name;
	int deptId;

	int num = 0;
	if (ifs.is_open())
	{
		while (ifs>>id && ifs>>name && ifs>>deptId)
		{
			num++;
		}
	}
	return num;
}

//��ʼ��ְ����Ϣ
void WorkerManager::initEmp()
{
	ifstream ifs(FILENAME, ios::in);
	int id;
	string name;
	int deptId;

	Worker *worker = NULL;
	int index = 0;
	if (ifs.is_open())
	{
		while (ifs >> id && ifs >> name && ifs >> deptId)
		{
			switch (deptId)
			{
			case 1://��ͨԱ��
				worker = new Employee(id, name, deptId);
				break;
			case 2://����
				worker = new Manager(id, name, deptId);
				break;
			case 3://�ϰ�
				worker = new Boss(id, name, deptId);
				break;
			default:
				break;
			}

			this->empArray[index++] = worker;
		}
	}
	ifs.close();
}

//��ʾְ����Ϣ
void WorkerManager::showEmp()
{
	if (this->empArray == NULL)
	{
		cout << "��ǰû��ְ����" << endl;
	}
	else
	{
		for (int i = 0; i < this->empNum; i++)
		{
			this->empArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
int WorkerManager::empIsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->empNum; i++)
	{
		if (this->empArray[i]->id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//ɾ��ְ����Ϣ
void WorkerManager::deleteEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "ְ����Ϣ�ļ������ڣ��޷�ִ��ɾ��������" << endl;
	}
	else
	{
		int id;
		cout << "������Ҫɾ����ְ����ţ�" << endl;
		cin >> id;
		int index = this->empIsExist(id);

		if (index != -1)
		{
			for (int i = 0; i < this->empNum - 1; i++)
			{
				this->empArray[i] = this->empArray[i + 1];
			}

			//����ְ������;
			this->empNum--;

			//����ְ���ļ�
			this->save();
			cout << "ɾ��ְ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�޸�ְ����Ϣ
void WorkerManager::editEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "ְ����Ϣ�ļ������ڣ��޷�ִ��ɾ��������" << endl;
	}
	else
	{
		int id;
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		cin >> id;

		int index = this->empIsExist(id);
		if (index != -1)
		{
			//�ͷ�֮ǰ�ĵ�ַ
			delete this->empArray[index];

			int newId = 0;
			string newName = "";
			int newDeptId = 0;

			cout << "�ҵ�" << id << "��ְ�����������±�ţ�" << endl;
			cin >> newId;
			cout << "�����������֣�" << endl;
			cin >> newName;
			cout << "��ѡ���²��ţ�" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> newDeptId;

			Worker* worker = NULL;
			switch (newDeptId)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}
			this->empArray[index] = worker;
			this->save();
			cout << "�޸ĳɹ���" << endl;
		}
		else
		{
			cout << "��ְ�������ڣ��޸�ʧ�ܣ�" << endl;
		}
		system("pause");
		system("cls");
	}
}

//����ְ��
void WorkerManager::findEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "ְ����Ϣ�ļ������ڣ��޷�ִ�в��Ҳ�����" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1.����Ų���" << endl;
		cout << "2.����������" << endl;

		int mode;
		cin >> mode;

		if (mode == 1)//����Ų���
		{
			int id;
			cout << "������Ա����ţ�" << endl;
			cin >> id;

			int index = this->empIsExist(id);
			if (index != -1)
			{
				cout << "�����Ǹ�Ա����Ϣ��" << endl;
				this->empArray[index]->showInfo();
			}
			else
			{
				cout << "û���ҵ�" << id << "��Ա����" << endl;
			}
		}
		else if (mode == 2)//����������
		{ 
			string name = "";
			cout << "������Ҫ��ѯ��������" << endl;
			cin >> name;

			bool flag = true;
			for (int i = 0; i < this->empNum; i++)
			{
				if (this->empArray[i]->name == name)
				{
					cout << "����Ϊְ����Ϣ��" << endl;
					this->empArray[i]->showInfo();
					flag = false;
				}
			}

			if (flag)
			{
				cout << "û���ҵ�" << name << "��" << endl;
			}
		}
		else//�������
		{
			cout << "��������ȷѡ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

//��Ա������
void WorkerManager::sortEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "ְ����Ϣ�ļ������ڣ��޷�ִ�����������" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.�������" << endl;
		cout << "2.��Ž���" << endl;
		int mode;
		cin >> mode;

		for (int i = 0; i < this->empNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->empNum; j++)
			{
				//����
				if (mode == 1)
				{
					if (this->empArray[i]->id > this->empArray[j]->id)
					{
						minOrMax = j;
					}
				}
				else if (mode == 2)
				{
					//����
					if (this->empArray[i]->id < this->empArray[j]->id)
					{
						minOrMax = j;
					}
				}

				if (i != minOrMax)
				{
					Worker* temp = NULL;
					temp = this->empArray[minOrMax];
					this->empArray[minOrMax] = this->empArray[i];
					this->empArray[i] = temp;
				}
			}
		}

		//������Ϣ�ļ�
		this->save();
		cout << "����ɹ���" << endl;
		this->showEmp();
	}
}

//����ļ�
void WorkerManager::emptyFile()
{
	if (this->fileIsEmpty)
	{
		cout << "ְ����Ϣ�ļ������ڣ��޷�ִ����ղ�����" << endl;
	}
	else
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//��ն�������
		for (int i = 0; i < this->empNum; i++)
		{
			if (this->empArray[i] != NULL)
			{
				delete this->empArray[i];
				this->empArray[i] = NULL;
			}
		}
		delete[] this->empArray;
		this->empArray = NULL;
		this->empNum = 0;
		this->fileIsEmpty = true;
		cout << "��ճɹ���" << endl;
		system("pause");
		system("cls");
	}
}

//�˳�����
void WorkerManager::exitSystem()
{
	cout << "ллʹ�ã�" << endl;
	system("pause");
	exit(0);
}

WorkerManager::~WorkerManager()
{
	for (int i = 0; i < this->empNum; i++)
	{
		if (this->empArray[i] != NULL)
		{
			delete this->empArray[i];
			this->empArray[i] = NULL;
		}
	}

	delete[] this->empArray;
	
}
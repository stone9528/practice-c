#include"workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs(FILENAME, ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		this->empNum = 0;
		this->empArray = NULL;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->empNum = 0;
		this->empArray = NULL;
		this->fileIsEmpty = true;
		ifs.close();
	}

	//文件存在且数据不为空
	int size = this->getEmpNum();
	this->empNum = size;
	this->empArray = new Worker*[size];
	this->fileIsEmpty = false;
	this->initEmp();
}

//菜单显示
void WorkerManager::showMenu()
{
	cout << "************************************" << endl;
	cout << "******* 欢迎使用职工管理系统 *******" << endl;
	cout << "********** 0.退出管理程序 **********" << endl;
	cout << "********** 1.增加职工信息 **********" << endl;
	cout << "********** 2.显示职工信息 **********" << endl;
	cout << "********** 3.删除离职职工 **********" << endl;
	cout << "********** 4.修改职工信息 **********" << endl;
	cout << "********** 5.查找职工信息 **********" << endl;
	cout << "********** 6.按照编号排序 **********" << endl;
	cout << "********** 7.清空所有文档 **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//增加员工
void WorkerManager::addEmplyee()
{
	int newEmpNum = 0;//新员工数
	cout << "请输入要新增的员工数：" << endl;
	cin >> newEmpNum;

	if (newEmpNum > 0)
	{
		int newSize = newEmpNum + this->empNum;//新的员工总数
		Worker** newSpace = new Worker*[newSize];//新的存放空间

		//转移之前的数据到新空间
		for (int i = 0; i < this->empNum; i++)
		{
			newSpace[i] = this->empArray[i];
		}

		int id;//新员工的编号
		string name;//新员工的名字
		int deptId;//新员工的部门编号
		//输入新员工信息
		for (int i = 0; i < newEmpNum; i++)
		{
			cout << "请输入第" << i + 1 << "个新员工的编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新员工的名字：" << endl;
			cin >> name;
			cout << "请选择第" << i + 1 << "个新员工的部门：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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

		//释放之前的空间
		delete[] this->empArray;

		//更新地址空间
		this->empArray = newSpace;

		//更新职工人数
		this->empNum = newSize;

		//更新文件存在标志
		if (this->fileIsEmpty)
		{
			this->fileIsEmpty = false;
		}

		cout << "成功增加" << newEmpNum << "个新员工" << endl;

		//保存到文件中
		this->save();
	}
	else
	{
		cout << "输入的数字错误" << endl;
	}

	system("pause");
	system("cls");
}

//将职工信息保存到文件中
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

//统计文件中职工人数
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

//初始化职工信息
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
			case 1://普通员工
				worker = new Employee(id, name, deptId);
				break;
			case 2://经理
				worker = new Manager(id, name, deptId);
				break;
			case 3://老板
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

//显示职工信息
void WorkerManager::showEmp()
{
	if (this->empArray == NULL)
	{
		cout << "当前没有职工！" << endl;
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

//判断职工是否存在
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

//删除职工信息
void WorkerManager::deleteEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "职工信息文件不存在，无法执行删除操作！" << endl;
	}
	else
	{
		int id;
		cout << "请输入要删除的职工编号：" << endl;
		cin >> id;
		int index = this->empIsExist(id);

		if (index != -1)
		{
			for (int i = 0; i < this->empNum - 1; i++)
			{
				this->empArray[i] = this->empArray[i + 1];
			}

			//更新职工人数;
			this->empNum--;

			//更新职工文件
			this->save();
			cout << "删除职工成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改职工信息
void WorkerManager::editEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "职工信息文件不存在，无法执行删除操作！" << endl;
	}
	else
	{
		int id;
		cout << "请输入要修改的职工编号：" << endl;
		cin >> id;

		int index = this->empIsExist(id);
		if (index != -1)
		{
			//释放之前的地址
			delete this->empArray[index];

			int newId = 0;
			string newName = "";
			int newDeptId = 0;

			cout << "找到" << id << "号职工，请输入新编号：" << endl;
			cin >> newId;
			cout << "请输入新名字：" << endl;
			cin >> newName;
			cout << "请选择新部门：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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
			cout << "修改成功！" << endl;
		}
		else
		{
			cout << "该职工不存在，修改失败！" << endl;
		}
		system("pause");
		system("cls");
	}
}

//查找职工
void WorkerManager::findEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "职工信息文件不存在，无法执行查找操作！" << endl;
	}
	else
	{
		cout << "请选择查找方式：" << endl;
		cout << "1.按编号查找" << endl;
		cout << "2.按姓名查找" << endl;

		int mode;
		cin >> mode;

		if (mode == 1)//按编号查找
		{
			int id;
			cout << "请输入员工编号：" << endl;
			cin >> id;

			int index = this->empIsExist(id);
			if (index != -1)
			{
				cout << "以下是该员工信息：" << endl;
				this->empArray[index]->showInfo();
			}
			else
			{
				cout << "没有找到" << id << "号员工！" << endl;
			}
		}
		else if (mode == 2)//按姓名查找
		{ 
			string name = "";
			cout << "请输入要查询的姓名：" << endl;
			cin >> name;

			bool flag = true;
			for (int i = 0; i < this->empNum; i++)
			{
				if (this->empArray[i]->name == name)
				{
					cout << "以下为职工信息：" << endl;
					this->empArray[i]->showInfo();
					flag = false;
				}
			}

			if (flag)
			{
				cout << "没有找到" << name << "！" << endl;
			}
		}
		else//输入错误
		{
			cout << "请输入正确选项！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//对员工排序
void WorkerManager::sortEmp()
{
	if (this->fileIsEmpty)
	{
		cout << "职工信息文件不存在，无法执行排序操作！" << endl;
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1.编号升序" << endl;
		cout << "2.编号降序" << endl;
		int mode;
		cin >> mode;

		for (int i = 0; i < this->empNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->empNum; j++)
			{
				//升序
				if (mode == 1)
				{
					if (this->empArray[i]->id > this->empArray[j]->id)
					{
						minOrMax = j;
					}
				}
				else if (mode == 2)
				{
					//降序
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

		//更新信息文件
		this->save();
		cout << "排序成功！" << endl;
		this->showEmp();
	}
}

//清空文件
void WorkerManager::emptyFile()
{
	if (this->fileIsEmpty)
	{
		cout << "职工信息文件不存在，无法执行清空操作！" << endl;
	}
	else
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//清空堆区数据
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
		cout << "清空成功！" << endl;
		system("pause");
		system("cls");
	}
}

//退出程序
void WorkerManager::exitSystem()
{
	cout << "谢谢使用！" << endl;
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
#include"speechManager.h"

//构造
SpeechManager::SpeechManager()
{
	this->initSpeech();

	//创建选手
	this->creatSpeaker();

	//读取往届记录
	this->loadRecord();
}

//显示菜单
void SpeechManager::showMenu()
{
	cout << "********************************" << endl;
	cout << "********欢迎参加演讲比赛********" << endl;
	cout << "********1. 开始演讲比赛 ********" << endl;
	cout << "********2. 查看往届记录 ********" << endl;
	cout << "********3. 清空比赛记录 ********" << endl;
	cout << "********4. 退出比赛程序 ********" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

//比赛初始化
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->speakerMap.clear();
	this->record.clear();
	this->index = 1;
}

//初始化比赛选手
void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.length(); i++)
	{
		Speaker sp;
		string name = "选手";
		name += nameSeed[i];
		sp.name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0;
		}

		this->v1.push_back(i + 1001);
		this->speakerMap.insert(make_pair(i + 1001,sp));
	}
}

//开始比赛
void SpeechManager::startSpeech()
{
	//第一轮抽签
	this->speechDraw();

	//第一轮比赛
	this->speechContest();

	this->showScore();

	//第二轮比赛
	this->index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();

	this->saveRecord();
	cout << "比赛完毕！" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->index << "轮比赛开始抽签" << endl;
	cout << "-------------------------------" << endl;
	cout << "抽签结果如下：" << endl;

	if (this->index == 1)
	{
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else
	{
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
	}
	cout << endl;
}

//比赛过程
void SpeechManager::speechContest()
{
	cout << "第" << this->index << "轮正式比赛开始" << endl;
	multimap<double, int, greater<double>> groupScore;
	vector<int> temp;
	if (this->index == 1)
	{
		temp = this->v1;
	}
	else
	{
		temp = this->v2;
	}

	//遍历每个参赛者
	int num = 0;
	for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
	{
		num++;

		//为每位参赛者打分
		deque<double> de;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			de.push_back(score);
		}

		//去掉最低最高分，取平均分
		sort(de.begin(), de.end(), greater<double>());
		de.pop_back();
		de.pop_front();
		double sum = accumulate(de.begin(), de.end(), 0.0f);
		double avg = sum / de.size();

		//将成绩保存
		this->speakerMap[*it].score[this->index - 1] = avg;

		groupScore.insert(make_pair(avg,*it));

		//6人一组输出
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "组成绩如下：" << endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second
					<< "\t姓名：" << this->speakerMap[it->second].name
					<< "\t成绩：" << it->first << endl;
			}

			//取前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->index == 1)
				{
					this->v2.push_back(it->second);
				}
				else
				{
					this->vVictory.push_back(it->second);
				}
			}
			count = 0;
			groupScore.clear();
		}
	}
	cout << "第" << this->index << "轮比赛结束" << endl;
}

//显示晋级选手
void SpeechManager::showScore()
{
	cout << "-------------第" << this->index << "轮比赛晋级选手------------" << endl;
	vector<int> v;
	if (this->index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it
			<< "\t姓名：" << this->speakerMap[*it].name
			<< "\t成绩：" << this->speakerMap[*it].score[this->index-1] << endl;
	}

	system("pause");
	system("cls");
}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->speakerMap[*it].score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "记录已经保存！" << endl;
}

//读取往届记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	
	ifs.putback(ch);
	this->fileIsEmpty = false;
	string data;

	int index = 0;
	string temp;
	vector<string> v;
	while (ifs>>data)
	{
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}

			temp = data.substr(start, pos - start);
			start = pos + 1;
			v.push_back(temp);
		}
		this->record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

//显示往届记录
void SpeechManager::showRecord()
{
	for (map<int,vector<string>>::iterator it = this->record.begin(); it != record.end(); it++)
	{
		cout << "第" << it->first + 1 << "届"
			<< " 冠军编号：" << it->second[0] << " 成绩：" << it->second[1]
			<< " 亚军编号：" << it->second[2] << " 成绩：" << it->second[3]
			<< " 季军编号：" << it->second[4] << " 成绩：" << it->second[5] << endl;
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "是否删除？" << endl;
	cout << "1.确认" << endl;
	cout << "2.取消" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ifstream ifs("speech.csv", ios::trunc);
		ifs.close();

		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();
	}
}

//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}


//析构
SpeechManager::~SpeechManager()
{
}
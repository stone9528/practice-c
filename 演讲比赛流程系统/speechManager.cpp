#include"speechManager.h"

//����
SpeechManager::SpeechManager()
{
	this->initSpeech();

	//����ѡ��
	this->creatSpeaker();

	//��ȡ�����¼
	this->loadRecord();
}

//��ʾ�˵�
void SpeechManager::showMenu()
{
	cout << "********************************" << endl;
	cout << "********��ӭ�μ��ݽ�����********" << endl;
	cout << "********1. ��ʼ�ݽ����� ********" << endl;
	cout << "********2. �鿴�����¼ ********" << endl;
	cout << "********3. ��ձ�����¼ ********" << endl;
	cout << "********4. �˳��������� ********" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

//������ʼ��
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->speakerMap.clear();
	this->record.clear();
	this->index = 1;
}

//��ʼ������ѡ��
void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.length(); i++)
	{
		Speaker sp;
		string name = "ѡ��";
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

//��ʼ����
void SpeechManager::startSpeech()
{
	//��һ�ֳ�ǩ
	this->speechDraw();

	//��һ�ֱ���
	this->speechContest();

	this->showScore();

	//�ڶ��ֱ���
	this->index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();

	this->saveRecord();
	cout << "������ϣ�" << endl;
	system("pause");
	system("cls");
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->index << "�ֱ�����ʼ��ǩ" << endl;
	cout << "-------------------------------" << endl;
	cout << "��ǩ������£�" << endl;

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

//��������
void SpeechManager::speechContest()
{
	cout << "��" << this->index << "����ʽ������ʼ" << endl;
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

	//����ÿ��������
	int num = 0;
	for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
	{
		num++;

		//Ϊÿλ�����ߴ��
		deque<double> de;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			de.push_back(score);
		}

		//ȥ�������߷֣�ȡƽ����
		sort(de.begin(), de.end(), greater<double>());
		de.pop_back();
		de.pop_front();
		double sum = accumulate(de.begin(), de.end(), 0.0f);
		double avg = sum / de.size();

		//���ɼ�����
		this->speakerMap[*it].score[this->index - 1] = avg;

		groupScore.insert(make_pair(avg,*it));

		//6��һ�����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "��ɼ����£�" << endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second
					<< "\t������" << this->speakerMap[it->second].name
					<< "\t�ɼ���" << it->first << endl;
			}

			//ȡǰ����
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
	cout << "��" << this->index << "�ֱ�������" << endl;
}

//��ʾ����ѡ��
void SpeechManager::showScore()
{
	cout << "-------------��" << this->index << "�ֱ�������ѡ��------------" << endl;
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
		cout << "��ţ�" << *it
			<< "\t������" << this->speakerMap[*it].name
			<< "\t�ɼ���" << this->speakerMap[*it].score[this->index-1] << endl;
	}

	system("pause");
	system("cls");
}

//�����¼
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
	cout << "��¼�Ѿ����棡" << endl;
}

//��ȡ�����¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	//�ļ�������
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ�Ϊ��
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

//��ʾ�����¼
void SpeechManager::showRecord()
{
	for (map<int,vector<string>>::iterator it = this->record.begin(); it != record.end(); it++)
	{
		cout << "��" << it->first + 1 << "��"
			<< " �ھ���ţ�" << it->second[0] << " �ɼ���" << it->second[1]
			<< " �Ǿ���ţ�" << it->second[2] << " �ɼ���" << it->second[3]
			<< " ������ţ�" << it->second[4] << " �ɼ���" << it->second[5] << endl;
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ɾ����" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.ȡ��" << endl;
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

//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}


//����
SpeechManager::~SpeechManager()
{
}
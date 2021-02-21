#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include<numeric>
#include<algorithm>
#include<fstream>
#include"speaker.h"
using namespace std;

class SpeechManager
{
public:
	SpeechManager();

	//��ʾ�˵�
	void showMenu();

	//������ʼ��
	void initSpeech();

	//��ʼ������ѡ��
	void creatSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//��������
	void speechContest();

	//��ʾ����ѡ��
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ�����¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//�˳�ϵͳ
	void exitSystem();

	~SpeechManager();

	//��һ�ֱ���ѡ�ֱ������
	vector<int> v1;

	//�ڶ��ֱ���ѡ������
	vector<int> v2;

	//���ʤ��ѡ�ֱ������
	vector<int> vVictory;

	//��ű�źͶ�Ӧѡ������
	map<int, Speaker> speakerMap;

	//��������
	int index;

	//��¼�ļ��Ƿ�Ϊ�ձ�־
	bool fileIsEmpty;

	//�����¼����
	map<int, vector<string>> record;

private:

};
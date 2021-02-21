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

	//显示菜单
	void showMenu();

	//比赛初始化
	void initSpeech();

	//初始化比赛选手
	void creatSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛过程
	void speechContest();

	//显示晋级选手
	void showScore();

	//保存记录
	void saveRecord();

	//读取往届记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	//退出系统
	void exitSystem();

	~SpeechManager();

	//第一轮比赛选手编号容器
	vector<int> v1;

	//第二轮比赛选手容器
	vector<int> v2;

	//获得胜利选手编号容器
	vector<int> vVictory;

	//存放编号和对应选手容器
	map<int, Speaker> speakerMap;

	//比赛轮数
	int index;

	//记录文件是否为空标志
	bool fileIsEmpty;

	//往届记录容器
	map<int, vector<string>> record;

private:

};
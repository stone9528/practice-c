//¿œ∞Â¿‡
#pragma once
#include"worker.h"
using namespace std;

class Boss :public Worker
{
public:
	Boss(int id, string name, int deptId);

	virtual void showInfo();
	virtual string getDeptName();
};
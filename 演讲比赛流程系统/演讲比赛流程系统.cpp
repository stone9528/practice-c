#include"speechManager.h"
#include<string>

int main()
{
	SpeechManager manager;

	int menu;//菜单号

	while (true)
	{
		manager.showMenu();
		cout << "请输入菜单号：" << endl;
		cin >> menu;
		switch (menu)
		{
		case 1://开始演讲比赛
			manager.startSpeech();
			break;
		case 2://查看往届记录
			manager.showRecord();
			break;
		case 3://清空比赛记录
			break;
		case 4://退出系统
			manager.exitSystem();
			break;
		default:
			cout << "请输入正确的菜单号！" << endl;
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
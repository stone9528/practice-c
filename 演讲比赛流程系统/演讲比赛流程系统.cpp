#include"speechManager.h"
#include<string>

int main()
{
	SpeechManager manager;

	int menu;//�˵���

	while (true)
	{
		manager.showMenu();
		cout << "������˵��ţ�" << endl;
		cin >> menu;
		switch (menu)
		{
		case 1://��ʼ�ݽ�����
			manager.startSpeech();
			break;
		case 2://�鿴�����¼
			manager.showRecord();
			break;
		case 3://��ձ�����¼
			break;
		case 4://�˳�ϵͳ
			manager.exitSystem();
			break;
		default:
			cout << "��������ȷ�Ĳ˵��ţ�" << endl;
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
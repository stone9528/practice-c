#include"workerManager.h"

int main()
{
	WorkerManager workerManager;

	int chioce = 0;//�û�ѡ��Ĳ˵�
	while (true)
	{
		workerManager.showMenu();
		cout << "������˵��ţ�" << endl;
		cin >> chioce;

		switch (chioce)
		{
		case 0://�˳�����
			workerManager.exitSystem();
			break;
		case 1://����ְ��
			workerManager.addEmplyee();
			break;
		case 2://��ʾְ��
			workerManager.showEmp();
			break;
		case 3://ɾ��ְ��
			workerManager.deleteEmp();
			break;
		case 4://�޸�ְ��
			workerManager.editEmp();
			break;
		case 5://����ְ��
			workerManager.findEmp();
			break;
		case 6://ְ������
			workerManager.sortEmp();
			break;
		case 7://����ĵ�
			workerManager.emptyFile();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
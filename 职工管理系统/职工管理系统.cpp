#include"workerManager.h"

int main()
{
	WorkerManager workerManager;

	int chioce = 0;//用户选择的菜单
	while (true)
	{
		workerManager.showMenu();
		cout << "请输入菜单号：" << endl;
		cin >> chioce;

		switch (chioce)
		{
		case 0://退出程序
			workerManager.exitSystem();
			break;
		case 1://增加职工
			workerManager.addEmplyee();
			break;
		case 2://显示职工
			workerManager.showEmp();
			break;
		case 3://删除职工
			workerManager.deleteEmp();
			break;
		case 4://修改职工
			workerManager.editEmp();
			break;
		case 5://查找职工
			workerManager.findEmp();
			break;
		case 6://职工排序
			workerManager.sortEmp();
			break;
		case 7://清空文档
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
#include"AVL.h"

int accept;
AVLTree origin;

int main() {
	while (1) {
		cout << "��������Ҫ��������֣�����-1���������룩��" << endl;
		cin >> accept;
		if (accept != -1) {
			origin.Insert_all(accept);
		}
		else {
			break;
		}
	}
	origin.print_all();
	while (1) {
		cout << endl << "������Ҫɾ�������֣������ѯ������Ӧ�Ľ��ͻ��˳���:" << endl;
		cin >> accept;
		if (origin.Remove_all(accept))
			origin.print_all();
		else
			break;
	}
	origin.print_all();
	return 0;
}
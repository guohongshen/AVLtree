#include"AVL.h"

int accept;
AVLTree origin;

int main() {
	while (1) {
		cout << "请输入需要插入的数字（输入-1来结束插入）：" << endl;
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
		cout << endl << "请输入要删除的数字（如果查询不到对应的结点就会退出）:" << endl;
		cin >> accept;
		if (origin.Remove_all(accept))
			origin.print_all();
		else
			break;
	}
	origin.print_all();
	return 0;
}
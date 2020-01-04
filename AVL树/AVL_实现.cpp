#include"AVL.h"

void AVLTree::destory(AVLNode* x) {
};
void AVLTree::RotateL(AVLNode*& y) {
	AVLNode* subL = y;
	y = subL->right;
	subL->right = y->left;
	y->left = subL;
	y->bf = subL->bf = 0;
};
void AVLTree::RotateR(AVLNode*& y) {
	AVLNode* subR = y;
	y = subR->left;
	subR->left = y->right;
	y->right = subR;
	y->bf = subR->bf = 0;
};
void AVLTree::RotateLR(AVLNode*& y) {
	AVLNode* subR = y;
	AVLNode* subL = subR->left;
	y = subL->right;
	subL->right = y->left;
	y->left = subL;
	if (y->bf <= 0)subL->bf = 0;
	else subL->bf = -1;
	subR->left = y->right;
	y->right = subR;
	if (y->bf == -1)subR->bf = 1;
	else subR->bf = 0;
	y->bf = 0;
};
void AVLTree::RotateRL(AVLNode*& y) {
	AVLNode* subL = y;
	AVLNode* subR = subL->right;
	y = subR->left;
	subR->left = y->right;
	y->right = subR;
	if (y->bf >= 0)subR->bf = 0;
	else subR->bf = 1;
	subL->right = y->left;
	y->left = subL;
	if (y->bf == 1)subL->bf = -1;
	else subL->bf = 0;
	y->bf = 0;
};
AVLNode* AVLTree::Search(const int x, AVLNode* y) {
	if (y == nullptr)return nullptr;
	else if (x < y->data)return Search(x, y->left);
	else if (x > y->data)return Search(x, y->right);
	else return y;
};
bool AVLTree::Insert(AVLNode*& y, int& x) {
	AVLNode* pr = nullptr;
	AVLNode* p = y;
	AVLNode* q;
	int d;
	stack<AVLNode*> st;
	while (p != nullptr) {
		if (x == p->data)return false;
		pr = p;st.push(pr);
		if (x < p->data)p = p->left;
		else p = p->right;
	}
	p = new AVLNode(x);
	if (p == nullptr) {
		cout << "存储空间不足！" << endl;exit(1);
	}
	if (pr == nullptr) {
		y = p;return true;
	}
	if (x < pr->data)pr->left = p;
	else pr->right = p;
	while (st.empty() == false) {
		pr = st.top();
		st.pop();
		if (p == pr->left)pr->bf--;
		else pr->bf++;
		if (pr->bf == 0)break;
		if (pr->bf == 1 || pr->bf == -1)
			p = pr;
		else {
			d = (pr->bf < 0) ? -1 : 1;
			if (p->bf == d) {
				if (d == -1)RotateR(pr);
				else RotateL(pr);
			}
			else {
				if (d == -1)RotateLR(pr);
				else RotateRL(pr);
			}
			break;
		}
	}
	if (st.empty() == true)y = pr;
	else {
		q = st.top();
		if (q->data > pr->data)q->left = pr;
		else q->right = pr;
	}
	return true;
};
//bool AVLTree::Remove(int& x, AVLNode*& y) {
//	AVLNode* pr = nullptr;
//	AVLNode* p = y;
//	AVLNode* q = nullptr;
//	AVLNode* ppr = nullptr;
//	int d = 0;
//	int dd = 0;
//	int flag = 0;
//	stack<AVLNode*>st;
//	while (p != nullptr) {//根结点不为空，寻找要删除的结点。
//		if (x == p->data)break;//找到。
//		pr = p;st.push(pr);//栈记忆查找路径。
//		if (x < p->data)p = p->left;
//		else p = p->right;//进入其中一个子树。
//	}
//	if (p == nullptr)return false;//如果根结点为空或者未找到需要删除的结点，就退出。
//	if (p->left != nullptr && p->right != nullptr) {//此处表示找到该结点。
//		pr = p;st.push(pr);
//		q = p->left;
//		while (q->right != nullptr) {
//			pr = q;st.push(pr);q = q->right;
//		}
//		p->data = q->data;
//		p = q;//被删除的结点转化为q，q为原p左子树的最大值。
//	}
//	if (p->left != nullptr)q = p->left;
//	else q = p->right;//q应该是空。
//	if (pr == nullptr)y = q;
//	else {
//		if (pr->left == p) {
//			flag = 0;
//			pr->left = q;
//		}
//		else { flag = 1;y->right = q; }
//		while (st.empty() == false) {
//			pr = st.top();/*!*/
//			st.pop();/*!*/
//			//st.pop();//! st.pop(pr);
//			if (pr->left == q&&flag==0)
//				pr->bf++;
//			else pr->bf--;
//			if (st.empty() == false) {
//				ppr = st.top();/*!*/
//				st.pop();/*!*/
//				//ppr = st.top();//! st.top(ppr);
//				dd = (ppr->left == pr) ? -1 : 1;
//			}
//			else dd = 0;
//			if (pr->bf == 1 || pr->bf == -1)break;
///**/
//			if (pr->bf != 0) {
//				if (pr->bf < 0) { d = -1;q = pr->left; }
//				else { d = 1;q = pr->right; }
//				if (q->bf == 0) {
//					if(d==-1)
//					{RotateR(pr);pr->bf = 1;pr->left->bf = -1;}
//					else { RotateL(pr);pr->bf = -1;pr->right->bf = 1; }
//					break;
//				}
//				if (q->bf == d) {
//					if (d == -1)RotateR(pr);
//					else RotateL(pr);
//				}
//				else {
//					if (d == -1)RotateLR(pr);
//					else RotateRL(pr);
//				}
//				if (dd == -1)ppr->left = pr;
//				else if (dd == 1)ppr->right = pr;
//			}
//			q = pr;
//		}
//		if (st.empty() == true)y = pr;
//	}
//	delete p;return true;
//};
void AVLTree::print_all() {
	string ss = " ";
	print(root, ss);
}
void AVLTree::print(AVLNode* x, string ss) {
	if (x == NULL)
		return;
	ss += "   ";
	print(x->right, ss);
	cout << ss << x->data << endl;
	print(x->left, ss);
};
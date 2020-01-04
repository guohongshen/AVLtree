#include"AVL.h"

bool AVLTree::Remove(int& x, AVLNode*& y)
{
	AVLNode * p = y;
	AVLNode* pr = nullptr;
	AVLNode* ppr = nullptr;
	AVLNode* q = nullptr;
	stack<AVLNode*> st;
	int sign, lable;    //符号标记
	int flag = 0;       //子树标记
	while (p != nullptr) {
		if (p->data == x)//找到跳出循环
			break;
		pr = p;
		st.push(pr);
		if (p->data > x)
			p = p->left;
		else
			p = p->right;
	}
	if (p == nullptr) {//未找到，返回
		return false;
	}
	else if (p->left != nullptr && p->right != nullptr) {//*1*有两个子树。将有两个孩子的节点转化为只有一个孩子的节点，方法是寻找它中序遍历的直接前驱或后继，这里是寻找前驱。
		pr = p;
		st.push(pr);//要删除的先结点入栈
		q = p->left;
		while (q->right != nullptr) {
			pr = q;
			st.push(pr);//旧结点入栈
			q = q->right;
		}
		p->data = q->data;//覆盖要删除的节点，此时要删除的结点就是q指向的结点。
		p = q;
	}
	if (p->left != nullptr) {//*2*只有左子树。这样的判断方式会导致删除一个节点下两个没有孩子节点的节点时，由于左孩子均为空，直接跳入else
		q = p->left;//那就只拿它的左子树就可以了。
	}
	else {
		q = p->right;
	}
	if (pr == nullptr)//删除的是根结点，且根结点最多有一个子女，那就直接删除即可。
		y = q;
	else {//否则。
		if (pr->left == p) {   //上面直接跳入else，但我们在此处加上flag，用来识别它到底是pr的左孩子还是右孩子。
			flag = 0;
			pr->left = q;//注意此时的p只有一个子女。
		}
		else {
			flag = 1;
			pr->right = q;
		}
		while (!st.empty()) {
			pr = st.top();
			st.pop();
			if (pr->left == q && flag == 0)//此处flag=0，防止pr的左孩子为空，右孩子同样为空，直接进入else
				pr->bf++;
			else
				pr->bf--;
			if (!st.empty())
			{
				ppr = st.top();
				if (ppr->left == pr)
				{
					sign = -1;//sign用来识别是祖父节点的左孩子还是右孩子。
					flag = 0;
				}
				else {
					sign = 1;
					flag = 1;
				}
			}
			else
				sign = 0;//栈空，它的祖先节点不存在，pr即为根节点，但是这里也要写上，否则sign的值会遗留下来
			if (pr->bf == -1 || pr->bf == 1)
				break;//已经平衡，直接跳出
			if (pr->bf != 0) {//bf为+2/-2
				if (pr->bf < 0) {//-2
					lable = -1;//lable表示父节点符号
					q = pr->left;
				}
				else {//2
					lable = 1;
					q = pr->right;
				}
				if (q->bf == 0) {//pr的较高子树的头节点bf为0
					if (lable == -1) {//右单旋
						RotateR(pr);
						pr->bf = 1;
						pr->right->bf = -1;
					}
					else {
						RotateL(pr);//左单旋
						pr->bf = -1;
						pr->left->bf = 1;
					}
					break;//直接跳出
				}
				if (q->bf == lable) {
					lable == 1 ? RotateL(pr) : RotateR(pr);
				}
				else {
					lable == -1 ? RotateLR(pr): RotateRL(pr);
				}
				if (sign == -1)
					ppr->left = pr;
				else if (sign == 1)
					ppr->right = pr;
			}
			q = pr;
		}
		if (st.empty())//栈为空，根节点
			y = pr;
		else {
			ppr = st.top();
			if (ppr->data > pr->data)
				ppr->left = pr;
			else
				ppr->right = pr;
		}
	}
	delete p;
	p = nullptr;
	return true;
}
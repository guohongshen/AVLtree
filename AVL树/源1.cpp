#include"AVL.h"

bool AVLTree::Remove(int& x, AVLNode*& y)
{
	AVLNode * p = y;
	AVLNode* pr = nullptr;
	AVLNode* ppr = nullptr;
	AVLNode* q = nullptr;
	stack<AVLNode*> st;
	int sign, lable;    //���ű��
	int flag = 0;       //�������
	while (p != nullptr) {
		if (p->data == x)//�ҵ�����ѭ��
			break;
		pr = p;
		st.push(pr);
		if (p->data > x)
			p = p->left;
		else
			p = p->right;
	}
	if (p == nullptr) {//δ�ҵ�������
		return false;
	}
	else if (p->left != nullptr && p->right != nullptr) {//*1*�����������������������ӵĽڵ�ת��Ϊֻ��һ�����ӵĽڵ㣬������Ѱ�������������ֱ��ǰ�����̣�������Ѱ��ǰ����
		pr = p;
		st.push(pr);//Ҫɾ�����Ƚ����ջ
		q = p->left;
		while (q->right != nullptr) {
			pr = q;
			st.push(pr);//�ɽ����ջ
			q = q->right;
		}
		p->data = q->data;//����Ҫɾ���Ľڵ㣬��ʱҪɾ���Ľ�����qָ��Ľ�㡣
		p = q;
	}
	if (p->left != nullptr) {//*2*ֻ�����������������жϷ�ʽ�ᵼ��ɾ��һ���ڵ�������û�к��ӽڵ�Ľڵ�ʱ���������Ӿ�Ϊ�գ�ֱ������else
		q = p->left;//�Ǿ�ֻ�������������Ϳ����ˡ�
	}
	else {
		q = p->right;
	}
	if (pr == nullptr)//ɾ�����Ǹ���㣬�Ҹ���������һ����Ů���Ǿ�ֱ��ɾ�����ɡ�
		y = q;
	else {//����
		if (pr->left == p) {   //����ֱ������else���������ڴ˴�����flag������ʶ����������pr�����ӻ����Һ��ӡ�
			flag = 0;
			pr->left = q;//ע���ʱ��pֻ��һ����Ů��
		}
		else {
			flag = 1;
			pr->right = q;
		}
		while (!st.empty()) {
			pr = st.top();
			st.pop();
			if (pr->left == q && flag == 0)//�˴�flag=0����ֹpr������Ϊ�գ��Һ���ͬ��Ϊ�գ�ֱ�ӽ���else
				pr->bf++;
			else
				pr->bf--;
			if (!st.empty())
			{
				ppr = st.top();
				if (ppr->left == pr)
				{
					sign = -1;//sign����ʶ�����游�ڵ�����ӻ����Һ��ӡ�
					flag = 0;
				}
				else {
					sign = 1;
					flag = 1;
				}
			}
			else
				sign = 0;//ջ�գ��������Ƚڵ㲻���ڣ�pr��Ϊ���ڵ㣬��������ҲҪд�ϣ�����sign��ֵ����������
			if (pr->bf == -1 || pr->bf == 1)
				break;//�Ѿ�ƽ�⣬ֱ������
			if (pr->bf != 0) {//bfΪ+2/-2
				if (pr->bf < 0) {//-2
					lable = -1;//lable��ʾ���ڵ����
					q = pr->left;
				}
				else {//2
					lable = 1;
					q = pr->right;
				}
				if (q->bf == 0) {//pr�Ľϸ�������ͷ�ڵ�bfΪ0
					if (lable == -1) {//�ҵ���
						RotateR(pr);
						pr->bf = 1;
						pr->right->bf = -1;
					}
					else {
						RotateL(pr);//����
						pr->bf = -1;
						pr->left->bf = 1;
					}
					break;//ֱ������
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
		if (st.empty())//ջΪ�գ����ڵ�
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
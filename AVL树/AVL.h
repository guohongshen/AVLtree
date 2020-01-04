#include<iostream>
#include<stack>
using namespace std;

struct AVLNode {
	int bf;
	int data;
	AVLNode* left;
	AVLNode* right;
	AVLNode(int x, AVLNode* l = nullptr, AVLNode* r = nullptr) {
		data = x;
		left = l;
		right = r;
		bf = 0;
	}
};
class AVLTree {
private:
	AVLNode* root;
protected:
	void RotateL(AVLNode*& y);
	void RotateR(AVLNode*& y);
	void RotateLR(AVLNode*& y);
	void RotateRL(AVLNode*& y);
public:
	AVLTree() {
		root = nullptr;
	}
	AVLTree(int x) {
		root = new AVLNode(x);
	}
	~AVLTree() {
		destory(root);
	};
	void destory(AVLNode* y);
	AVLNode* Search_all(const int x) {
		Search(x, root);
	};
	AVLNode* Search(const int x, AVLNode* y);
	bool Insert_all(int& x) {
		Insert(root, x);
		return true;
	};
	bool Insert(AVLNode*& y, int& x);
	bool Remove_all(int& x) {
		return Remove(x, root);
	};
	bool Remove(int& x, AVLNode*& y);
	void print_all();
	void print(AVLNode* x, string ss);
};
#include"SeqStack.h"

template<typename T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) {
	elements = new T[maxSize];
	assert(elements != nullptr);
};
template<typename T>
void SeqStack<T>::overflowProcess() {
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray = nullptr) {
		cout << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}
	for (int i = 0;i < top;++i) {
		newArray[i] = elements[i];
	}
	maxSize = maxSize + stackIncreament;
	delete[]elements;
	//elemets = newArray;!!!!!�����Ӧ�ü�//�ģ�
};
template<typename T>
void SeqStack<T>::Push(const T& x) {
	if (IsFull() == true)overflowProcess();
	elements[++top] = x;
};
template<typename T>
bool SeqStack<T>::Pop(T& x) {
	if (IsEmpty() == true)return false;
	x = elements[top--];
	return true;
};
template<typename T>
bool SeqStack<T>::getTop(T& x) {
	if (IsEmpty() == true)return false;
	x = elements[top];
	return true;
};
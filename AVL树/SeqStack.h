#include<assert.h>
#include<iostream>
using namespace std;

const int maxSize = 50;
const int stackIncreament = 20;

template<typename T>
class SeqStack {
private:
	T* elements;
	int top;
	int maxSize;
	void overflowProcess();
public:
	SeqStack(int sz = 50);
	~SeqStack() {
		delete[]elements;
	}
	void Push(const T& x);
	bool Pop(T& x);
	bool getTop(T& x);
	bool IsEmpty()const {
		return(top == -1) ? true : false;
	}
	bool IsFull()const {
		return(top == maxSize - 1) ? true : false;
	}
	int getSize()const {
		return top + 1;
	}
	void MakeEmpty() {
		top = -1;
	}
};
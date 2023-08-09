#pragma once
#include "ListNode.h"

class Queue
{
private:
	ListNode* head, * tail;
public:
	~Queue();
	void makeEmpty();
	bool isEmpty();
	void Enqueue(int data);
	int Dequeue();
	void Print();
};
#pragma once
#include "ListNode.h"
#include <iostream>
using namespace std;

class AdjList
{
public:
	ListNode* head;
	ListNode* tail;
	AdjList();
	~AdjList();
	void Append(int data);
	void Remove(int data);
	friend ostream& operator <<(ostream& os, const AdjList& list)
	{
		ListNode* temp = list.head;
		while (temp != nullptr)
		{
			cout << temp->data << "->";
			temp = temp->next;
		}
		cout << endl;
		return os;
	}
};
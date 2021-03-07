#include "Queue.h"
#include <iostream>
using namespace std;

Queue::~Queue()
{
	ListNode* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void Queue::makeEmpty()
{
	head = tail = nullptr;
}

bool Queue::isEmpty()
{
	return head == nullptr;
}

void Queue::Enqueue(int data)
{
	ListNode* newNode = new ListNode;
	newNode->data = data;
	newNode->next = nullptr;
	if (isEmpty())
		head = tail = newNode;
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}

int Queue::Dequeue()
{
	if (!isEmpty())
	{
		ListNode* temp = head;
		head = head->next;
		int data = temp->data;
		delete temp;
		return data;
	}
	else
		return -1;
}

void Queue::print()
{
	ListNode* temp = head;
	while (temp != nullptr)
	{
		cout << "<-" << temp->data;
		temp = temp->next;
	}
	cout << endl;
}
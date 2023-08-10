#include "Queue.h"
#include <iostream>
using namespace std;

Queue::~Queue()
{
	ListNode* temp;

	while (this->head != nullptr)
	{
		temp = this->head;
		head = this->head->next;
		delete temp;
	}
}

void Queue::makeEmpty()
{
	this->head = this->tail = nullptr;
}

bool Queue::isEmpty()
{
	return this->head == nullptr;
}

void Queue::Enqueue(int data)
{
	ListNode* newNode = new ListNode;

	newNode->data = data;
	newNode->next = nullptr;
	if (this->isEmpty())
	{
		this->head = this->tail = newNode;
	}
	else
	{
		this->tail->next = newNode;
		this->tail = newNode;
	}
}

int Queue::Dequeue()
{
	if (!this->isEmpty())
	{
		ListNode* temp = this->head;

		this->head = this->head->next;
		int data = temp->data;
		delete temp;
		return data;
	}
	else
	{
		return -1;
	}
}
#include "AdjList.h"

AdjList::AdjList()
{
	this->head = this->tail = nullptr;
}

AdjList::~AdjList()
{
	ListNode* temp = nullptr;

	while (this->head != nullptr)
	{
		temp = this->head;
		this->head = this->head->next;
		delete temp;
	}
}

void AdjList::Append(int data)
{
	ListNode* newNode = new ListNode();
	newNode->data = data;
	newNode->next = nullptr;

	if (this->head == nullptr)
	{
		this->head = this->tail = newNode;
	}
	else
	{
		this->tail->next = newNode;
		this->tail = newNode;
	}
}

//todo errors? come here
void AdjList::Remove(int data)
{
	ListNode* temp = head;
	ListNode* next = nullptr;

	if (temp->data == data)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
	next = temp->next;
	while (next != nullptr)
	{
		if (next->data == data)
		{
			temp->next = next->next;
			delete next;
		}
	}
}
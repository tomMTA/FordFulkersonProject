#include "AdjList.h"

AdjList::AdjList()
{
	head = tail = nullptr;
}

AdjList::~AdjList()
{
	ListNode* temp = nullptr;

	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void AdjList::Append(int data)
{
	ListNode* newNode = new ListNode();
	newNode->data = data;
	newNode->next = nullptr;

	if (head == nullptr)
	{
		head = tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
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
#include "AdjList.h"

AdjList::AdjList()
{
	head = tail = nullptr;
}

AdjList::AdjList(AdjList&& other)
{
	head = other.head;
	tail = other.tail;
	other.head = other.tail = nullptr;
}

AdjList::~AdjList()
{
	ListNode* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void AdjList::Append(int data)
{
	ListNode* newNode = new ListNode;
	newNode->data = data;
	newNode->next = nullptr;
	if (head == nullptr)
		head = tail = newNode;
	else
	{
		tail->next = newNode;
		tail = tail->next;
	}
}

void AdjList::remove(int data)
{
	ListNode* temp = head;
	if (temp->data == data)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
	ListNode* next = temp->next;
	while (next != nullptr)
	{
		if (next->data == data)
		{
			temp->next = next->next;
			delete next;
		}
	}
}
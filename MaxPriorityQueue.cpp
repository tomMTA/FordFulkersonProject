#include <iostream>
#include "MaxPriorityQueue.h"
#include "Utility.h"

using namespace std;
using namespace utility;

MaxPriorityQueue::~MaxPriorityQueue()
{
	if (!this->IsEmpty())
	{
		delete[] this->heapArr;
		delete[] this->priorityArr;
	}
}

MaxPriorityQueue::MaxPriorityQueue(double values[], int n)
{
	this->heapArr = new QueueNode[n];
	this->priorityArr = new int[n];
	this->size = n;
	for (int v = 1; v <= n; v++)
	{
		this->heapArr[v - 1].key = v;
		this->heapArr[v - 1].value = values[v];
		this->priorityArr[v - 1] = v - 1;
	}
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		this->FixHeapDown(i);
	}
}

int MaxPriorityQueue::DeleteMax()
{
	if (this->IsEmpty())
	{
		quitWithMsg("Error: Attempted to delete max of empty queue");
	}
	this->size--;
	this->Swap(0, this->size);
	this->FixHeapDown(0);
	return this->heapArr[size].key;
}

bool MaxPriorityQueue::IsEmpty()
{
	return this->size == 0;
}

void MaxPriorityQueue::IncreaseValue(int v, double newValue)
{
	int i = this->priorityArr[v - 1];
	if (this->heapArr[i].value < newValue)
	{
		this->heapArr[i].value = newValue;
		this->FixHeapUp(i);
	}
}

int MaxPriorityQueue::Parent(int i)
{
	return (i - 1) / 2;
}

int MaxPriorityQueue::Left(int i)
{
	return 2 * i + 1;
}

int MaxPriorityQueue::Right(int i)
{
	return 2 * i + 2;
}

void MaxPriorityQueue::FixHeapDown(int i)
{
	int max = i;
	int left = this->Left(i);
	int right = this->Right(i);

	if (left < size) //is there a left son
	{
		if (this->heapArr[left].value > this->heapArr[i].value)
		{
			max = left;
		}
	}
	if (right < size) //is there a right son
	{
		if (this->heapArr[right].value > this->heapArr[max].value)
		{
			max = right;
		}
	}
	if (max != i)
	{
		this->Swap(i, max);
		this->FixHeapDown(max);
	}
}

void MaxPriorityQueue::FixHeapUp(int i)
{
	int parent = this->Parent(i);
	while ((i > 0) && this->heapArr[parent].value < this->heapArr[i].value)
	{
		this->Swap(i, parent);
		i = parent;
	}
}

void MaxPriorityQueue::Swap(int i, int j)
{
	int u = this->heapArr[i].key;
	int v = this->heapArr[j].key;
	this->priorityArr[u - 1] = j;
	this->priorityArr[v - 1] = i;
	QueueNode temp = this->heapArr[i];
	this->heapArr[i] = this->heapArr[j];
	this->heapArr[j] = temp;
}
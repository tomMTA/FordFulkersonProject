#include "MaxPriorityQueue.h"
#include <iostream>
using namespace std;

MaxPriorityQueue::~MaxPriorityQueue()
{
	if (!this->IsEmpty())
	{
		delete[] this->arr;
		delete[] this->priority;
	}
}

void MaxPriorityQueue::Build(double d[], int n)
{
	this->arr = new QueueNode[n];
	this->priority = new int[n];
	this->size = n;
	for (int v = 1; v <= n; v++)
	{
		this->arr[v - 1].data = v;
		this->arr[v - 1].key = d[v];
		this->priority[v - 1] = v - 1;
	}
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		this->FixHeapDown(i);
	}
}

//todo understand this and then reform and validate not empty (what to return?)
int MaxPriorityQueue::DeleteMax()
{
	this->size--;
	this->Swap(0, size);
	this->FixHeapDown(0);
	return this->arr[size].data;
}

bool MaxPriorityQueue::IsEmpty()
{
	return this->size == 0;
}

void MaxPriorityQueue::IncreaseKey(int v, double newKey)
{
	int i = this->priority[v - 1];
	if (this->arr[i].key < newKey)
	{
		this->arr[i].key = newKey;
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
		if (this->arr[left].key > this->arr[i].key)
		{
			max = left;
		}
	}
	if (right < size) //is there a right son
	{
		if (this->arr[right].key > this->arr[max].key)
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
	while ((i > 0) && this->arr[this->Parent(i)].key < this->arr[i].key)
	{
		this->Swap(i, this->Parent(i));
		i = this->Parent(i);
	}
}

void MaxPriorityQueue::Swap(int a, int b)
{
	int u = arr[a].data;
	int v = arr[b].data;
	int tmp = priority[u - 1];
	priority[u - 1] = b;
	priority[v - 1] = a;
	QueueNode temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void MaxPriorityQueue::Print()
{
	for (int i = 0; i < size; i++)
		cout << i << ". (" << arr[i].data << "," << arr[i].key << ")" << "\t" << arr[i].data << " is #" <<
		priority[arr[i].data - 1] + 1 << " in heap arr" << endl;
}
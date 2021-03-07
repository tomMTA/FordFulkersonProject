#include "MaxPriorityQueue.h"
#include <iostream>
using namespace std;

MaxPriorityQueue::~MaxPriorityQueue()
{
	if (!IsEmpty())
	{
		delete[]arr;
		delete[]place;
	}
}

void MaxPriorityQueue::Build(double* d, int n)
{
	arr = new QueueNode[n];
	place = new int[n];
	size = n;
	for (int v = 1; v <= n; v++)
	{
		arr[v - 1].data = v;
		arr[v - 1].key = d[v];
		place[v - 1] = v - 1;
	}
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		FixHeapDown(i);
	}
}

int MaxPriorityQueue::DeleteMax()
{
	size--;
	Swap(0, size);
	FixHeapDown(0);
	return arr[size].data;
}

bool MaxPriorityQueue::IsEmpty()
{
	return size == 0;
}

void MaxPriorityQueue::IncreaseKey(int v, double newKey)
{
	int i = place[v - 1];
	if (arr[i].key < newKey)
	{
		arr[i].key = newKey;
		FixHeapUp(i);
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
	int left = Left(i);
	int right = Right(i);

	if (left < size)//is there a left son
	{
		if (arr[left].key > arr[i].key)
		{
			max = left;
		}
	}

	if (right < size)//is there a right son
	{
		if (arr[right].key > arr[max].key)
		{
			max = right;
		}
	}
	if (max != i)
	{
		Swap(i, max);
		FixHeapDown(max);
	}
}

void MaxPriorityQueue::FixHeapUp(int i)
{
	while ((i > 0) && arr[Parent(i)].key < arr[i].key)
	{
		Swap(i, Parent(i));
		i = Parent(i);
	}
}

void MaxPriorityQueue::Swap(int a, int b)
{
	int u = arr[a].data;
	int v = arr[b].data;
	int tmp = place[u - 1];
	place[u - 1] = b;
	place[v - 1] = a;
	QueueNode temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void MaxPriorityQueue::print()
{
	for (int i = 0; i < size; i++)
		cout << i << ". (" << arr[i].data << "," << arr[i].key << ")" << "\t" << arr[i].data << " is #" <<
		place[arr[i].data - 1] + 1 << " in heap arr" << endl;
}
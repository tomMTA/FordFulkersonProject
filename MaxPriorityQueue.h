#pragma once
struct QueueNode
{
	int key;		//vertex u
	double value;	//d[u]
};

class MaxPriorityQueue
{
private:
	QueueNode* heapArr;			//array of {key=u, data=d[u]}
	int* priorityArr;			//priority[u] = index of u in heap's arr
	int size;					//heap logical size
	static int Parent(int i);	//index of parent in heap's arr
	static int Left(int i);		//index of left son in heap's arr
	static int Right(int i);	//index of right son in heap's arr
	void FixHeapDown(int i);	//compare & swap with sons until leaf
	void FixHeapUp(int i);		//compare & swap with parents until root
	void Swap(int i, int j);	//swap i, j and keep track of each vertex's index in heap's arr
public:
	~MaxPriorityQueue();
	MaxPriorityQueue(double values[], int n);	//FLOYD. values[u-1] = value of u
	int DeleteMax();
	bool IsEmpty();
	void IncreaseValue(int v, double newKey);	//v is vertex from V={1..n}
};
#pragma once
struct QueueNode
{
	int data;		//vertex u
	double key;		//d[u]
};

class MaxPriorityQueue
{
private:
	QueueNode* arr;				//array of {data=u, key=d[u]}
	int* priority;					//place[u] = index of u in heap's arr
	int size;					//heap logical size
	static int Parent(int i);	//index of parent
	static int Left(int i);		//index of left son
	static int Right(int i);	//index of right son
	void FixHeapDown(int i);	//compare with sons until leaf
	void FixHeapUp(int i);		//compare with parents until roots
	void Swap(int a, int b);	//swap V[a], V[b] and keep track of each vertex's index in heap's arr
public:
	~MaxPriorityQueue();
	void Build(double d[], int n);		//FLOYD. d[] contains keys of n nodes of {1..n}
	int DeleteMax();
	bool IsEmpty();
	void IncreaseKey(int v, double newKey);		//v is vertex from V={1..n}
	void Print();
};
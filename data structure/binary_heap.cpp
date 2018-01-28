const int MaxSize = 100000; // MaxSize is the capability of the heap

struct BinaryHeap
{
	int heap[MaxSize + 1], n;

	BinaryHeap() : n(0) {}
	BinaryHeap(int ArraySize, int array[]) : n(0) // initialize the heap from array
	{
		for (int i = 0; i < ArraySize; i++)
			heap[++n] = array[i];
		for (int i = n >> 1; i; i--)
			down(i);
	}

	void up(int p)
	{
		int x = heap[p];

		while ((p >> 1) && (x > heap[p >> 1])) // move up if the node has a higher priority than its parent
		{
			heap[p] = heap[p >> 1];
			p >>= 1;
		}
		heap[p] = x;
	}

	void down(int p)
	{
		int x = heap[p];

		while ((p << 1) <= n)
		{
			int m = (p << 1);
			m += m < n && heap[m] < heap[m + 1];

			if (heap[m] > x) // move down if the node has a lower priority than one of its children
			{
				heap[p] = heap[m];
				p = m;
			}
			else
				break;
		}
		heap[p] = x;
	}

	void push(int x)
	{
		heap[++n] = x;
		up(n);
	}
	
	int top()
	{
		return heap[1];
	}

	bool pop() // bool deletes the root of the heap and returns true if the queue is not empty
	{
		if (n)
		{
			swap(heap[1], heap[n]);
			n--;
			down(1);
			return true;
		}
		else
			return false;
	}

	bool empty()
	{
		return n == 0;
	}

	int size()
	{
		return n;
	}
};
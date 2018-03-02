/*by Zhaobo Ding*/
const int MaxN = 100000; // MaxN stores the length of BIT array.

class BIT
{
private:
	int tree[MaxN + 1], n = MaxN;

	int lowbit(int x) // calculate the leftmost 1 in x
	{
		return x & (-x);
	}

public:
	BIT(int MaxSize) : n(MaxSize) {}
	BIT(int ArraySize, int array[]) : n(ArraySize)
	{
		for (int i = 1; i <= ArraySize; i++)
			add(i, array[i]);
	}

	void add(int x, int s)
	{
		for (int i = x; i <= n; i += lowbit(i))
			tree[i] += s;
	}

	int getsum(int x)
	{
		int ans = 0;

		for (int i = x; i; i -= lowbit(i))
			ans += tree[i];

		return ans;
	}
};

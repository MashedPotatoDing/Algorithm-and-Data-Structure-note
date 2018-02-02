class DisJointSet
{
	private:
		int n; // n is the size of Disjoint Set
		vector <int> par, rank;

	public:
		DisJointSet(int n) : par(n), rank(n) // initialize
		{
			for (int i = 0; i < n; i++)
			{
				par[i] = i;
				rank[i] = 0;
			}
		}

		int find(int x) // find the root of the set that x is in
		{
			if (par[i] == i)
				return i;
			else
				return par[i] = find(par[i]); // path compression
		}

		void union(int x, int y) // union the two trees that x and y are in
		{
			int a = find(x), b = find(y);

			if (a == b) return; // if x and y have been in the same set, we do not need to do anything

			if (rank[a] > rank[b]) // union by rank
				par[b] = a;
			else
			{
				par[a] = b;
				if (rank[a] == rank[b])
					rank[b]++;
			}
		}
};

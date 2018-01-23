/*by Zhaobo Ding*/
// we should call dfs(int rt) and sparse_table() after building the tree and call lca(int x, int y) for every inqury

const int Maxn = 10000, Bin = log2(Maxn);
// MaxN is the maximum number of vertices in the tree

int counter = 0;
int fst[Maxn + 1], vtx[Maxn * 2 + 1];
// fst[i] records the given number of vertex i and vertex[j] records the corresponding vertex of number j
int st[Maxn * 2 + 1][Bin + 2]; // sparse table for RMQ
bool visited[Maxn + 1];
vector<int> child[Maxn + 1];

void dfs(int rt) // build the Euler Tour Tree
{
	counter++;
	fst[rt] = counter;
	vtx[counter] = rt;
	visited[rt] = true;
	
	for (int i = 0; i < child[rt].size(); i++)
		if (!visited[child[rt][i]])
		{
			dfs(child[rt][i]);
			counter++;
			vtx[counter] = rt;
		}
	
	return;
}

void sparse_table() // RMQ initialization
{
	for (int i = 1; i <= counter; i++)
		st[i][0] = fst[vtx[i]];
	
	for (int j = 1; counter >> j; j++)
		for (int i = 1; i - 1 + (1 << j) <= counter; i++)
			st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	
	return;
}

int lca(int x, int y)
{
	int l = min(fst[x], fst[y]);
	int r = max(fst[x], fst[y]);
	int len = log2(r - l);
	
	return vtx[min(st[l][len], st[r + 1 - (1 << len)][len])];
}

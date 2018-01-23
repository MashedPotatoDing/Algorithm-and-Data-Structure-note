/*by Zhaobo Ding*/
// we should call init(int root) after building the tree and call lca(int x, int y) for every inqury

const int Maxn = 10000;
// MaxN is the maximum number of vertices in the tree

int depth[Maxn + 1], anc[Maxn + 1][Maxn + 1];
// anc[i][j] records the (2^j)th parent of i
int n, MaxDep;
// n is the number of vertices and 2^MaxDep is greater than the height of the tree
vector<int> child[Maxn + 1];

void dfs(int rt, int par) // we can use bfs instead to avoid stack overflow 
{
	depth[rt] = depth[par] + 1;
	if (depth[rt] >> MaxDep > 1) MaxDep++;
	anc[rt][0] = par; // anc[i][0] is parent of i
	
	for (int i = 0; i < child[rt].size(); i++)
		dfs(child[rt][i], rt);
	
	return;
}

void init(int root)
{
	MaxDep = 0;
	depth[root] = 0;
	dfs(root, root);
	
	for (int i = 1; i <= MaxDep; i++)
	{
		anc[root][i] = root;
		for (int j = 1; j <= n; j++)
			anc[j][i] = anc[anc[j][i - 1]][i - 1];
			// calculate anc[j][i] based on 2^i = 2^(i-1) + 2^(i-1)
	}
	
	return;
}

void move_up(int &x, int h) // move x h-step up
{
	for (int i = MaxDep; i >= 0; i--)
		if ((h >> i) & 1) x = anc[x][i];
	return;
}

int lca(int x, int y)
{
	if (depth[x] > depth[y])
		move_up(x, depth[x] - depth[y]);
	else
		move_up(y, depth[y] - depth[x]);
	// make x and y be on the same level
	
	if (x == y) return x;
	
	for (int i = MaxDep; i >= 0; i--)
		if (anc[x][i] != anc[y][i])
		{
			x = anc[x][i];
			y = anc[y][i];
		}
	
	if (x != y && anc[x][0] == anc[y][0])
		return anc[x][0];
	else
		return -1;
}

/*by Zhaobo Ding*/
const int MaxN = 10000;
// MaxN is the maximum number of vertices

int g[MaxN + 1][MaxN + 1];
// g[i][j] is the adjacent matrix of the graph

void floyd(int n)
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	
	return;
}

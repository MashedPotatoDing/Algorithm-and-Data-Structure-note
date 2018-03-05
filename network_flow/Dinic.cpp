/*by Zhaobo Ding*/

const int INF = 0x7FFFFFFF;
const int MaxN = 10000, MaxE = 100000;
// MaxN is the maximum number of vertices and MaxE is the maximum number of edges

int source, target, EdgeNum;
int src[MaxE + 1], tar[MaxE + 1], flow[MaxE + 1];
int  dep[MaxE + 1];
vector <int> head[MaxN + 1];

void addEdge(int x, int y, int w)
{
	EdgeNum++;
	src[EdgeNum] = x;
	tar[EdgeNum] = y;
	flow[EdgeNum] = w;
	head[x].push_back(EdgeNum);
}

void add(int x, int y, int w)
{
	addEdge(x, y, w);
	addEdge(y, x, 0);
}

bool bfs()
{
	memset(dep, 0, sizeof(dep));
	queue <int> q;
	while (!q.empty())
		q.pop();
	q.push(source);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < head[u].size(); i++)
			if (flow[head[u][i]] && dep[tar[head[u][i]]] == 0)
			{
				q.push(tar[head[u][i]]);
				dep[tar[head[u][i]]] = dep[u] + 1;
			}
	}

	return dep[target];
}

int dfs(int cur, int delta)
{
	if (cur == target) return delta;

	int ret = 0;
	for (int i = 0; i < head[u].size(); i++)
		if (dep[tar[head[cur][i]]] == dep[cur] + 1 && flow[head[cur][i]])
		{
			int f = dfs(tar[head[cur][i]], min(delta, flow[head[cur][i]]));
			flow[head[cur][i]] -= f;
			flow[head[cur][i] ^ 1] += f;
			ret += f;
			delta -= f;
		}

	return ret;
}

int Dinic()
{
	int ans = 0;
	while (bfs())
		ret += dfs(src, INF);

	return ans;
}
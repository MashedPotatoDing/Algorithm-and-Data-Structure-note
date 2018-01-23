/*by Zhaobo Ding*/
const int MaxN = 10000, INF = 0x7FFFFFFF;
// MaxN is the maximum number of vertices

struct AdjEdge
{
	int targ, len;
};
vector<AdjEdge> edge[MaxN + 1]; // edge[] is the adjacent list of the graph
int dist[MaxN + 1];
bool visited[MaxN + 1] = {0};

int prim(int n) // n is the number of vertices in graph
{
	int w = 0; // w records the sum of weight of edges in minimum spanning tree
	
	dist[1] = 0;
	for (int i = 2; i <= n; i++)
		dist[i] = INF;
	
	for (int i = 1; i <= n; i++)
	{
		int vtx = 0;
		for (int j = 1; j <= n; j++)
			if (!visited[j] && (vtx == 0 || dist[vtx] > dist[j]))
				vtx = j;
		// the process of finding shortest distance can be optimized by a heap
		
		if (vtx == 0) return -1;
		// vtx == 0 means the graph is not connected and thus has no spanning tree
		
		w += dist[vtx];
		visited[vtx] = true;
		for (int j = 0; j < edge[vtx].size(); j++)
			dist[edge[vtx][j].targ] = min(dist[edge[vtx][j].targ], edge[vtx][j].len);
	}
	
	return w;
}

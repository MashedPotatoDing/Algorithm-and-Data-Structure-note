/*by Zhaobo Ding*/

const int MaxN = 10000, INF = 0x7FFFFFFF;
// MaxN is the maximum number of vertices
struct AdjEdge
{
	int targ, len;
};
vector<AdjEdge> edge[MaxN + 1]; // edge[] is the adjacent list of the graph
int n, dist[MaxN + 1];
// dist[i] is the length of shortest path from source to i

void dijkstra(int src, int n)
{
	for (int i = 1; i <= n; i++)
	{
		dist[i] = INF;
		visited[i] = false;
	}
	
	dis[src] = 0;
	
	for (i = 1; i <= n; i++)
	{
		int m = 0;
		for (int j = 1; j <=n; j++)
			if (!visited[j] && m && dist[m] > dist[j])
				m = j;
		// the process of finding the closest vertex can be optimized by using fibonacci heap
			
		visited[m] = true;
		for (int j = 0; j <= edge[m].size(); j++)
		{
			int t = edge[m][j].tar, l = edge[m][j].len;
			if (!visited[t])
				dist[t] = min(dist[t], dist[m] + l); // update the distance
		}
	}
	
	return;
}

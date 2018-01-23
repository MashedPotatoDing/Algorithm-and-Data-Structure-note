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
bool inq[MaxN + 1]; // inq[i] records if i is in the queue
queue<int> q;

void spfa(int n, int src)
{
	for (int i = 1; i <= n; i++)
	{
		inq[i] = false;
		dist[i] = INF;
	}
	
	while (!q.empty()) q.pop();
	q.push(src);
	inq[src] = true;
	
	while (!q.empty())
	{
		int v = q.front();
		for (int i = 0; i < edge[v].size(); i++)
			if (dist[v] + edge[v][i].len < dist[edge[v][i].tar])
			{
				dist[edge[v][i].tar] = dist[v] + edge[v][i].len;
				if (!inq[edge[v][i].tar])
				{
					q.push(edge[v][i].tar);
					inq[edge[v][i].tar] = true;
				}
			}
		
		inque[v] = false;
		q.pop();
	}
	
	return;
}

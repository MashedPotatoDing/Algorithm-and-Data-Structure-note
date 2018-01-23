/*by Zhaobo Ding*/
// call dfs(n, x, -1, 0) for an arbitrary vertex x from every component in graph

const int MaxN = 10000;
// MaxN is the maximum number of vertices

struct AdjEdge
{
	int targ, len;
};
vector<AdjEdge> edge[MaxN + 1]; // edge[] is the adjacent list of the graph

int dep[MaxN + 1], mini[MaxN + 1];
/* dep[i] stores the depth of vertex i in the dfs tree and
   mini[i] stores the vertex with minimal depth that vertex i can reach */
bool visited[MaxN + 1];
int cut[MaxN + 1], bridge[MaxN + 1][MaxN + 1];
/* cut[i] stores whether vertex i is a cut and
   bridge[i][j] stores whether the edge joining i and j is a bridge */

void dfs(int n, int cur, int par, int depth)
/* n is the number of vertices in the graph, cur is current visiting vertex,
   par is the parent vertex of cur and depth is the depth of cur in the dfs tree */
{
	int child = 0;
	// child stores the number of children of vertex cur in dfs tree
	visited[cur] = true;
	dep[cur] = mini[cur] = depth;
	
	for (int i = 0; i < edge[cur].size(); i++)
	{
		int vtx = edge[cur][i].targ;
		if (vtx != par && visited[vtx])
			mini[cur] = min(mini[cur], dep[vtx]);
		// update mini[cur] by its visited ancestor
		
		if (!visited[vtx])
		{
			dfs(n, vtx, cur, depth + 1);
			child++;
			mini[cur] = min(mini[cur], mini[i]);
			// update mini[cur] by its children
			
			if (par != -1 && mini[i] >= dep[cur])
				cut[cur] = true;
			if (mini[i] > dep[cur])
				bridge[i][cur] = bridge[cur][i] = true;
		}
		if (par == -1 && child > 1) cut[cur] = true;
		// if vertex cur is the root, it is a cut if it has over 1 child in dfs tree
	}
	
	return;
}

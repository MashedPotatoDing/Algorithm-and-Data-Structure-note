/*by Zhaobo Ding*/

const int MaxN = 10000;
// MaxN is the maximum number of vertices

struct AdjEdge
{
	int targ, len;
};
vector<AdjEdge> edge[MaxN + 1]; // edge[] is the adjacent list of the graph
stack<int> st;

int colornum, counter;
int dfn[MaxN + 1], mini[MaxN + 1], color[MaxN + 1];
/* dfn[i] stores the number of vertex i in the dfs tree and
   mini[i] stores the vertex with minimal depth that vertex i can reach
   color[i] stores the color of vertex i where all vertices belonging to a
     strongly connected component share the same color*/

void tarjan(int x)
{
	dfn[x] = mini[x] = ++counter;
	st.push(x);
	
	for (int i = 0; i < edge[x].size(); i++)
	{
		int v = edge[x][i].targ;
		
		if (dfn[v])
			mini[x] = min(mini[x], dfn[v]);
			// update mini[cur] by its visited ancestor
		else
		{
			tarjan(v);
			mini[x] = min(mini[x], mini[v]);
			// update mini[cur] by its children
		}
	}
	
	if (dfn[x] == mini[x])
	/* if dep[x] == mini[x], all the vertices in the
	stack over x make up a strongly connected components */
	{
		int v;
		colornum++;
		
		do
		{
			v = st.top();
			st.pop();
			color[v] = colornum;
		}
		while (v != x);
	}
	
	return;
}

void scc(int n) // n is the number of vertices in the graph
{
	colornum = counter = 0;
	for (int i = 1; i <= n; i++)
		color[i] = dfn[i] = 0;
	
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0) tarjan(i);
		// call tarjan(int x) for all components in the graph
	
	return;
}

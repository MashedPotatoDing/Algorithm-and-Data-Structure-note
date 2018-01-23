/*by Zhaobo Ding*/
const int MaxN = 10000, MaxE = 100000;
// MaxN is the maximum number of vertices and MaxE is the maximum number of edges

struct Edge
{
	int src, tar, w;
}edge[MaxE + 1];
int par[MaxN + 1];

bool cmp(Edge x, Edge y) // comparison function for sorting by weight
{
	return x.w < y.w;
}

int GetParent(int x)
{
	if (x == par[x])
		return x;
	else
		return par[x] = GetParent(par[x]); // path compression
}

int kruscal(int n, int e) // n is the number of vertices and e is the number of edges
{
	int w = 0, cpn = n; // cpn records the number of components in the graph
	sort(edge + 1, edge + 1 + e, cmp); // sort by weight
	for (int i = 1; i <= n; i++)
		par[i] = i;
	// initialize the disjoint-set
	
	for (int i = 1; i <= e; i++)
	{
		int v1 = GetParent(edge[i].src);
		int v2 = GetParent(edge[i].tar);
		if (v1 == v2) continue;
		// v1 == v2 implies that the two vertices joint by edge[i] has been connected
		
		cpn--;
		par[v1] = v2; // union the sets containing v1 and v2
		
		w += edge[i].w; // w records the sum of weight of edges in minimum spanning tree
		if (cpn == 1) break;
		// when there is only one component, we have had the spanning tree
	}
	
	if (cpn != 1) return -1;
	// cpn == 1 gives that the graph is not connected and thus has no spanning tree
	
	return w;
}

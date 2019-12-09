// C++ program for Kruskal's algorithm to find Minimum 
// Spanning Tree of a given connected, undirected and 
// weighted graph 

#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

// Creating shortcut for an integer pair 
typedef  pair<int, int> Edge;

// Structure to represent a graph 
class Graph
{
public:
	// Constructor 
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	// Utility function to add an edge 
	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w, {u, v} });
	}

	// Function to find MST using Kruskal's 
	// MST algorithm 
	int kruskalMST();

private:
	int V, E;
	vector< pair<int, Edge> > edges;
};

// To represent Disjoint Sets 
class DisjointSets
{
public:

	DisjointSets(int n):
		n(n)
	{
		parent = new int[n + 1];
		rnk = new int[n + 1];
 
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;
			parent[i] = i;
		}
	}

	// Find the parent of a node 'u' 
	// Path Compression 
	int Find(int u)
	{
		/* Make the parent of the nodes in the path
		   from u--> parent[u] point to parent[u] */
		if (u != parent[u])
			parent[u] = Find(parent[u]);
		return parent[u];
	}

	// Union by rank 
	void Merge(int x, int y)
	{
		x = Find(x), y = Find(y);

		/* Make tree with smaller height
		   a subtree of the other tree  */
		if (rnk[x] > rnk[y])
			parent[y] = x;
		else // If rnk[x] <= rnk[y] 
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}

private:
	int* parent, * rnk;
	int n;
};

int Graph::kruskalMST()
{
	int mst_weight = 0; 

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	//проходимся по рёбрам
	vector< pair<int, Edge> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.Find(u);
		int set_v = ds.Find(v);

		//проверяем наличие цикла (если наборы одинаковые - цикл)
		if (set_u != set_v)
		{
			// увеличиваем вес
			mst_weight += it->first;
			// сливаем наборы
			ds.Merge(set_u, set_v);
		}
	}

	return mst_weight;
}

int main()
{
	int n, m;
	cin >> n >> m;
	Graph g(n, m);

	int u, v, w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
	}
	   
	int mst_wt = g.kruskalMST();
	cout << mst_wt;

	return 0;
}
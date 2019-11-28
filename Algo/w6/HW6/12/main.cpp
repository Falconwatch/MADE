/*
Щербаков Игорь

Задача 12
Ребро неориентированного графа называется мостом, если удаление этого ребра из графа увеличивает число компонент связности.
Дан неориентированный граф, требуется найти в нем все мосты.
*/

#include <vector>
#include <iostream>
#include <list>


using namespace std;

void addEdge(list<int>* G, int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

// A recursive function that finds and prints bridges using 
// DFS traversal 
// u --> The vertex to be visited next 
// visited[] --> keeps tract of visited vertices 
// disc[] --> Stores discovery times of visited vertices 
// parent[] --> Stores parent vertices in DFS tree 
void bridgeUtil(vector<int>* bridges, list<int>* adj, int u, bool visited[], int disc[], int low[], int parent[])
{ 
	// A static variable is used for simplicity, we can  
	// avoid use of static variable by passing a pointer. 
	static int time = 0;

	visited[u] = true; 
	disc[u] = low[u] = ++time;

	// Go through all vertices aadjacent to this 
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;  // v is current adjacent of u 

		//ещё не заходили сюда - идём глубже 
		if (!visited[v])
		{
			parent[v] = u;
			bridgeUtil(bridges, adj, v, visited, disc, low, parent);

			// Check if the subtree rooted with v has a  
			// connection to one of the ancestors of u 
			if (low[u] > low[v]) {
				low[u] = low[v];
			}

			// If the lowest vertex reachable from subtree  
			// under v is  below u in DFS tree, then u-v  
			// is a bridge 
			if (low[v] > disc[u])
				bridges->push_back(v);
				//cout << u << " " << v << endl;
		}

		// Update low value of u for parent function calls. 
		else if (v != parent[u]) {
			if (low[u] > disc[v]) 
			{
				low[u] = disc[v];
			}
		}
	}
}

// DFS based function to find all bridges. It uses recursive  
// function bridgeUtil() 
void bridge(list<int>* G, int n)
{
	// Mark all the vertices as not visited 
	bool* visited = new bool[n];
	int* disc = new int[n];
	int* low = new int[n];
	int* parent = new int[n];

	vector<int>* bridges = new vector<int>;

	// Initialize parent and visited arrays 
	for (int i = 0; i < n; i++)
	{
		parent[i] = -1;
		visited[i] = false;
	}

	// Call the recursive helper function to find Bridges 
	// in DFS tree rooted with vertex 'i' 
	for (int i = 0; i < n; i++)
		if (visited[i] == false)
			bridgeUtil(bridges, G, i, visited, disc, low, parent);

	int n_bridges = bridges->size();
	cout << n_bridges <<endl;
	for (int i = 0; i < n_bridges; i++) {
		cout << (*bridges)[i] << endl;
	}
}

int main() {
	int n, m; //n-количество вершин
	cin >> n >> m;
	//создаём граф
	list<int>* G = new list<int>[n];
	//добавляем рёбра
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		addEdge(G, u-1, v-1);
	}

	bridge(G, n);
	return 0;
}
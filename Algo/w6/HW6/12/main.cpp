/*
Щербаков Игорь

Задача 12
Ребро неориентированного графа называется мостом, если удаление этого ребра из графа увеличивает число компонент связности.
Дан неориентированный граф, требуется найти в нем все мосты.
*/

#include <vector>
#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>


using namespace std;

void AddEdge(list<int>* G, int u, int v)
{
	if (find(G[u].begin(), G[u].end(), v)== G[u].end()) {
		G[u].push_back(v);
	}
	if (find(G[v].begin(), G[v].end(), u) == G[v].end()) {
		G[v].push_back(u);
	}
}

// Обход в глубину
void DFSBridge(vector<int>* bridges, list<int>* adj, int u, bool visited[], int disc[], int low[], int parent[])
{ 
	static int time = 0;

	visited[u] = true; 
	disc[u] = low[u] = ++time;

	// обходм все связанные вершины
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;

		//ещё не заходили сюда - идём глубже 
		if (!visited[v])
		{
			parent[v] = u;
			DFSBridge(bridges, adj, v, visited, disc, low, parent);

			if (low[u] > low[v]) {
				low[u] = low[v];
			}

			if (low[v] > disc[u])
				bridges->push_back(v);
		}
 
		else if (v != parent[u]) {
			if (low[u] > disc[v]) 
			{
				low[u] = disc[v];
			}
		}
	}
}

void FindBridges(list<int>* G, int n, string path)
{
	bool* visited = new bool[n];
	int* disc = new int[n];
	int* low = new int[n];
	int* parents = new int[n];

	vector<int>* bridges = new vector<int>;

	// Списки посещённых и родителей
	for (int i = 0; i < n; i++)
	{
		parents[i] = -1;
		visited[i] = false;
	}

	//для каждой вершины запускаем поиск моста
	for (int i = 0; i < n; i++)
		if (visited[i] == false)
			DFSBridge(bridges, G, i, visited, disc, low, parents);


	int n_bridges = bridges->size();
	ofstream outfile;
	outfile.open(path);
	outfile << n_bridges << endl;
	for (int i = 0; i < n_bridges; i++) {
		outfile << (*bridges)[i] << endl;
	}
	outfile.close();
}

//int main() {
//	ifstream infile;
//	infile.open("bridges.in");
//	int n, m; 
//	infile >> n >> m;
//	list<int>* G = new list<int>[n];
//	for (int i = 0; i < m; i++) {
//		int u, v;
//		infile >> u >> v;
//		AddEdge(G, u - 1, v - 1);
//	}
//	infile.close();
//
//	FindBridges(G, n, "bridges.out");
//	return 0;
//}
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
	if (find(G[u].begin(), G[u].end(), v) == G[u].end()) {
		G[u].push_back(v);
	}
	if (find(G[v].begin(), G[v].end(), u) == G[v].end()) {
		G[v].push_back(u);
	}
}

// Обход в глубину
void DFSBridge(vector<vector<int>>* bridges, list<int>* adj, int u, bool visited[], int disc[], int low[], int parent[])
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
				bridges->push_back(vector<int>({ u, v }));
		}

		else if (v != parent[u]) {
			if (low[u] > disc[v])
			{
				low[u] = disc[v];
			}
		}
	}
}

vector<vector<int>> FindBridges(list<int>* G, int n)
{
	bool* visited = new bool[n];
	int* disc = new int[n];
	int* low = new int[n];
	int* parents = new int[n];

	vector<vector<int>>* bridges = new vector<vector<int>>;

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

	vector<vector<int>> result;
	int n_bridges = bridges->size();
	result.push_back(vector<int>({ n_bridges, -1 }));
	for (int i = 0; i < n_bridges; i++) {
		result.push_back(vector<int>({ bridges[i][0][0], bridges[i][0][1]}));
	}
	return result;
}

int GetNum(vector<vector<int>> edge_numbers, int u, int v) {
	for (vector<int> edge_num : edge_numbers) {
		if ((edge_num[0] == u && edge_num[1] == v) ||
			(edge_num[0] == v && edge_num[1] == u)) {
			return edge_num[2];
		}
	}
	return -1;
}

//int main() {
//	ifstream infile;
//	infile.open("bridges.in");
//	int n, m;
//	infile >> n >> m;
//	list<int>* G = new list<int>[n];
//
//	vector<vector<int>> edge_numbers;
//	int total_edged = 0;
//
//	for (int i = 0; i < m; i++) {
//		int u, v;
//		infile >> u >> v;
//		AddEdge(G, u - 1, v - 1);
//		edge_numbers.push_back(vector<int>({ u - 1,v - 1,++total_edged }));
//	}
//	infile.close();
//
//	vector<vector<int>> r = FindBridges(G, n);
//	ofstream outfile;
//	outfile.open("bridges.out");
//	for (int i = 0; i < r.size(); i++) {
//		if (i == 0) {
//			outfile << r[i][0] <<endl;
//		}
//		else {
//			outfile << GetNum(edge_numbers, r[i][0], r[i][1]) << endl;
//		}
//	}
//	outfile.close();
//	 
//	return 0;
//}
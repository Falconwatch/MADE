#include <vector>
#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

class Graph {
public:
	Graph(int n) {
		g_.resize(n + 1); 
		used_.resize(n + 1);
		disc_.resize(n + 1); 
		up_.resize(n + 1);
		edges_added_ = 0;
	};

	void AddEdge(int a, int b) {
		g_[a].push_back(b); g_[b].push_back(a);
		edge_numbers_[CreateEdge(a, b)].push_back(++edges_added_);
	}

	set<int> FindBridges()
	{
		int n = g_.size();
		for (int i = 1; i < n; i++)
			if (!used_[i]) 
				DFS(i);
		return bridges_;
	}

private:
	vector<vector<int>> g_;
	vector<int> used_, disc_, up_;
	set<int> bridges_;
	map<pair<int, int>, vector<int>> edge_numbers_;
	int edges_added_;

	pair<int, int> CreateEdge(int a, int b)
	{
		if (a > b) swap(a, b);
		return make_pair(a, b);
	}

	void DFS(int v, int p = -1)
	{
		static int time = 1;
		int to;
		used_[v] = 1;
		disc_[v] = up_[v] = time++;
		for (int i = 0; i < g_[v].size(); i++)
		{
			to = g_[v][i];
			if (to == p)  continue;
			if (used_[to])
				up_[v] = min(up_[v], disc_[to]);
			else
			{
				DFS(to, v);
				up_[v] = min(up_[v], up_[to]);
				if (up_[to] > disc_[v]) {
					vector<int> one_edge_numbers = edge_numbers_[CreateEdge(v, to)];
					if (one_edge_numbers.size() == 1) //если ребро кратное, то не мост!
					{
						bridges_.insert(one_edge_numbers[0]);
					}
				}
			}
		}
	}
};


int main() {
	//читаем
	ifstream infile;
	infile.open("bridges.in");
	int n, m;
	infile >> n >> m;
	Graph G(n);
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		infile >> a >> b;
		G.AddEdge(a, b);
	}
	infile.close();

	//считаем
	set<int> Bridges = G.FindBridges();

	//выводим
	ofstream outfile;
	outfile.open("bridges.out");
	outfile << Bridges.size() << endl;
	for ( set<int>::iterator iter = Bridges.begin(); iter != Bridges.end(); iter++)
	{
		outfile << *iter << endl;
	}
	outfile.close();

	return 0;
}
#include <vector>
#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<vector<int> > G;
vector<int> used, d, up;
set<int> Bridges;
map<pair<int, int>, int> edge_numbers;

pair<int, int> Edge(int a, int b)
{
	if (a > b) swap(a, b);
	return make_pair(a, b);
}


void dfs(int v, int p = -1)
{
	static int time = 1;
	int i, to;
	used[v] = 1;
	d[v] = up[v] = time++;
	for (i = 0; i < G[v].size(); i++)
	{
		to = G[v][i];
		if (to == p)  continue;
		if (used[to])
			up[v] = min(up[v], d[to]);
		else
		{
			dfs(to, v);
			up[v] = min(up[v], up[to]);
			if (up[to] > d[v]) Bridges.insert(edge_numbers[Edge(v, to)]);
		}
	}
}

void FindBridges(int n)
{
	int i;

	for (i = 1; i <= n; i++)
		if (!used[i]) dfs(i);
}

int main() {
	ifstream infile;
	infile.open("bridges.in");
	int n, m;
	infile >> n >> m;
	G.resize(n + 1); used.resize(n + 1);
	d.resize(n + 1); up.resize(n + 1);
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		infile >> a >> b;
		G[a].push_back(b); G[b].push_back(a);
		edge_numbers[Edge(a, b)] = i;
	}
	infile.close();

	FindBridges(n);

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
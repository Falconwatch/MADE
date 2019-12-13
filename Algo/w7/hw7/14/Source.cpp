/*
�������� �����, MADE-11
������ 14-2
��� ����������������� ������� ����. ��������� ����� ��� ������������ ��������� ������ � ���� �����.
� ������� ��������� ��������.
*/
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

// ����� � �����
typedef  pair<int, int> Edge;
 
class Graph {
public:
	Graph(int V, int E);
	void AddEdge(int u, int v, int w);
	int FindMST();
private:
	int vertices_number_, edges_number_;
	vector<pair<int, Edge>> edges;
};

// ���� �������� �� ��������
class Components
{
public:
	Components(int n);
	int Find(int u);
	void Merge(int x, int y);
private:
	int* parents, * ranks;
	int n;
};

#pragma region Graph
Graph::Graph(int V, int E) : vertices_number_(V), edges_number_(E){}

void Graph::AddEdge(int u, int v, int w)
{
	edges.push_back({ w,{u,v} });
}

int Graph::FindMST()
{
	int mst_weight = 0; 

	sort(edges.begin(), edges.end());

	Components ds(vertices_number_);

	//���������� �� �����
	vector< pair<int, Edge> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.Find(u);
		int set_v = ds.Find(v);

		//��������� ������� ����� (���� ������ ���������� - ����)
		if (set_u != set_v)
		{
			cout << u << "-" << v << endl;
			// ����������� ���
			mst_weight += it->first;
			// ������� ������
			ds.Merge(set_u, set_v);
		}
	}

	return mst_weight;
}
#pragma endregion

#pragma region Components
Components::Components(int n) : n(n)
{
	parents = new int[n + 1];
	ranks = new int[n + 1];

	for (int i = 0; i <= n; i++)
	{
		ranks[i] = 0;
		parents[i] = i;
	}
}

int Components::Find(int u)
{
	//���� �������� �������� ������� ����������
	if (u != parents[u])
		parents[u] = Find(parents[u]);
	return parents[u];
}

void Components::Merge(int x, int y)
{
	x = Find(x), y = Find(y);

	//������������ ������� ������ � ��������
	if (ranks[x] > ranks[y])
		parents[y] = x;
	else
		parents[x] = y;

	if (ranks[x] == ranks[y])
		ranks[y]++;
}
#pragma endregion

int main()
{
	int n, m;
	cin >> n >> m;
	Graph g(n, m);

	int u, v, w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		g.AddEdge(u, v, w);
	}
	   
	int mst_wt = g.FindMST();
	cout << mst_wt;

	return 0;
}
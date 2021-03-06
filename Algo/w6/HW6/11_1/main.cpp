/*
�������� �����
11_1
��� ������������ ����������������� ����. ������� ���� ����������� �����.
*/
#include <iostream>
#include <vector>
#include <queue> 
#include <climits>

using namespace std;

class Graph {
public: 
	Graph(int size);
	void AddEdge(int u, int v);
	int FindShortestCycle(int n);
private:
	vector<vector<int>> G;
};

Graph::Graph(int size) {
	G.resize(size + 1);
}

void Graph::AddEdge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

int Graph::FindShortestCycle(int n)
{
	int min_length = INT_MAX;

	for (int i = 0; i < n; i++) {
		// ���������� ���������� - �����������
		vector<int> distances(n, INT_MAX);

		vector<int> parents(n, -1); // ��������
		distances[i] = 0; // ���������� �� ������ ���� - 0
		queue<int> q;

		// ���������� ��������� �������
		q.push(i);

		while (!q.empty()) {
			int x = q.front();
			q.pop();
			// ������� �����
			for (int child : G[x]) {
				//���� ��� �� ��������
				if (distances[child] == INT_MAX) {
					// ����� ����������
					distances[child] = 1 + distances[x];
					parents[child] = x;
					q.push(child);
				}
				// ��� ��������
				else if (parents[x] != child and parents[child] != x) {
					int distance = distances[x] + distances[child] + 1;
					if (min_length > distance) {
						min_length = distance;
					}
				}
			}
		}
	}
	if (min_length == INT_MAX)
		return -1;
	return min_length;
}

int main() {
	int n, m; //n-���������� ������
	cin >> n >> m;
	//������ ����
	Graph G(n);

	//��������� ����
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		G.AddEdge(u, v);
	}

	//�����
	cout << G.FindShortestCycle(n);
	return 0;
}
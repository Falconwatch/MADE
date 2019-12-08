/*
Щербаков Игорь
11_1
Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.
*/
#include <iostream>
#include <vector>
#include <queue> 
#include <climits>

using namespace std;


class Graph {
public: 
	Graph(int size) {
		G.resize(size + 1);

	}

	void AddEdge(int u, int v)
	{
		G[u].push_back(v);
		G[v].push_back(u);
	}


	int FindShortestCycle(int n)
	{
		int min_length = INT_MAX;

		for (int i = 0; i < n; i++) {
			// расстояние неизвестно - бесконечное
			vector<int> distances(n, INT_MAX);

			vector<int> parents(n, -1); // Родители
			distances[i] = 0; // Расстояние до самого себя - 0
			queue<int> q;

			// записываем начальную вершину
			q.push(i);

			while (!q.empty()) {
				int x = q.front();
				q.pop();
				// обходим детей
				for (int child : G[x]) {
					//если ещё не посещали
					if (distances[child] == INT_MAX) {
						// новое расстояние
						distances[child] = 1 + distances[x];
						parents[child] = x;
						q.push(child);
					}
					// уже посещали
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

private:
	vector<vector<int>> G;

};




int main() {
	int n, m; //n-количество вершин
	cin >> n >> m;
	//создаём граф
	Graph G(n);

	//добавляем рёбра
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		G.AddEdge(u, v);
	}

	//вывод
	cout << G.FindShortestCycle(n);
	return 0;
}
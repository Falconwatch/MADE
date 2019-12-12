/*
Щербаков Игорь, MADE-11
Задача 14-2
Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
С помощью алгоритма Крускала.
*/
#include<algorithm>
#include<vector>
#include<iostream>
#include<math.h>
#include"Graph.h"


#pragma region Graph
Graph::Graph(int V, int E) : vertices_number_(V), edges_number_(E) {}

void Graph::AddEdge(int u, int v, double w)
{
	edges.push_back({ w,{u,v} });
}

void Graph::AddVertice(double x, double y) {
	int added_vertices = vertices.size();
	for (int i=0; i< added_vertices;i++){
		auto vertice = vertices[i];
		double distance = (int)sqrt(pow(vertice.first - x, 2) + pow(vertice.first - y, 2));
		AddEdge(i, added_vertices, distance);
	}
	vertices.push_back({ x,y });
}


double Graph::FindMST()
{
	double mst_weight = 0;

	sort(edges.begin(), edges.end());

	Components ds(vertices_number_);

	//проходимся по рёбрам
	vector<pair<double, Edge> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.Find(u);
		int set_v = ds.Find(v);

		//проверяем наличие цикла (если наборы одинаковые - цикл)
		if (set_u != set_v)
		{
			cout << u << " - " << v << endl;
			// увеличиваем вес
			mst_weight += it->first;
			// сливаем наборы
			ds.Merge(set_u, set_v);
		}
	}

	return mst_weight;
}

double Graph::BruteForce() {
	vector<vector<double>> vertices_matrix (vertices_number_);
	for (int i = 0; i < vertices_matrix.size(); i++) {
		vertices_matrix[i].resize(vertices_number_);
	}


	for (auto edge : edges) {
		vertices_matrix[edge.second.first][edge.second.second] = edge.first;
		vertices_matrix[edge.second.second][edge.second.first] = edge.first;
	}

	vector<int> vertices_indexes;
	for (int i = 0; i < vertices_number_; i++) {
		vertices_indexes.push_back(i);
	}
	
	double min_path = INT_MAX;
	vector<int> min_path_nodes;
	int k = 0;
	do {
		k = vertices_indexes[0];
		double current_pathweight = 0;
		for (int i = 0; i < vertices_indexes.size(); i++) {
			current_pathweight += vertices_matrix[k][vertices_indexes[i]];
			k = vertices_indexes[i];
		}
		//вовзращаемся в начало
		current_pathweight += vertices_matrix[k][vertices_indexes[0]];

		if (current_pathweight < min_path) {
			min_path = current_pathweight;
			min_path_nodes = vertices_indexes;
		}
	} while (next_permutation(vertices_indexes.begin(), vertices_indexes.end()));

	cout << "Brute path:";
	for (auto mpn : min_path_nodes) {
		cout << mpn;
	}

	return min_path;
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
	//ищем родителя заданной вершины рекурсивно
	if (u != parents[u])
		parents[u] = Find(parents[u]);
	return parents[u];
}

void Components::Merge(int x, int y)
{
	x = Find(x), y = Find(y);

	//присоединяем маньшее дерево к большему
	if (ranks[x] > ranks[y])
		parents[y] = x;
	else
		parents[x] = y;

	if (ranks[x] == ranks[y])
		ranks[y]++;
}
#pragma endregion


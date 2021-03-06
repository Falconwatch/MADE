/*
�������� �����, MADE-11
������ 14-2
��� ����������������� ������� ����. ��������� ����� ��� ������������ ��������� ������ � ���� �����.
� ������� ��������� ��������.
*/
#include<algorithm>
#include<vector>
#include<iostream>
#include<math.h>
#include"Graph.h"
#include"Components.h"


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
		double distance = sqrt(pow(vertice.first - x, 2) + pow(vertice.first - y, 2));
		AddEdge(i, added_vertices, distance);
	}
	vertices.push_back({ x,y });
}


double Graph::FindMST()
{
	double mst_weight = 0;
	vector<int> mst_edges;

	sort(edges.begin(), edges.end());

	Components ds(vertices_number_);

	//���������� �� �����
	vector<pair<double, Edge> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.Find(u);
		int set_v = ds.Find(v);

		//��������� ������� ����� (���� ������ ���������� - ����)
		if (set_u != set_v)
		{
			// ����������� ���
			mst_weight += it->first;
			// ������� ������
			ds.Merge(set_u, set_v);
		}
	}
	//�.�. � ������ ����� ������� ������, ��������
	return mst_weight * 2;
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
		//������������ � ������
		current_pathweight += vertices_matrix[k][vertices_indexes[0]];

		if (current_pathweight < min_path) {
			min_path = current_pathweight;
			min_path_nodes = vertices_indexes;
		}
	} while (next_permutation(vertices_indexes.begin(), vertices_indexes.end()));

	return min_path;
}
#pragma endregion




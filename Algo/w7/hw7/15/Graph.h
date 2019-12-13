#include<algorithm>
#include<vector>
#include<iostream>
#include<math.h>


using namespace std;

// ребро
typedef  pair<int, int> Edge;
typedef  pair<double, double> Vertice;

class Graph {
public:
	Graph(int V, int E);
	void AddEdge(int u, int v, double w);
	void AddVertice(double x, double y);
	double FindMST();
	double BruteForce();
private:
	int vertices_number_, edges_number_;
	vector<pair<double, Edge>> edges;
	vector<Vertice> vertices;
};



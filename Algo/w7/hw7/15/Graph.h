#include<algorithm>
#include<vector>
#include<iostream>
#include<math.h>


using namespace std;

// נובנמ
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

// דנאפ נאחבטעûי םא ןמהדנאפû
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


#include<vector>
#include<algorithm>
#include<random>
#include<iostream>
#include<math.h>
#include"Graph.h"
#include<time.h>
#include <numeric>

const double M_PI = 3.141592653589793238462643383279502884;

using namespace std;

pair<double, double> estimateStatistics(vector<double> arr)
{
	double mean = accumulate(arr.begin(), arr.end(), 0.0 / arr.size());

	double sqDiff = 0;
	for (int i = 0; i < arr.size(); i++)
		sqDiff += (arr[i] - mean) * (arr[i] - mean);
	double var = sqDiff / arr.size();
	
	return { mean, var };
}

vector<pair<double, double>> GetPoints(int N){
	std::default_random_engine generator;
	uniform_real_distribution<> dis(0.0, 1.0);
	
	vector<pair<double, double>> result;
	double x, y;
	for (int i = 0; i < N; i++) {
		x = dis(generator);
		y = dis(generator);
		double z0 = cos(2 * M_PI * x) * sqrt(-2* log(x));
		double z1 = cos(2 * M_PI * y) * sqrt(-2 * log(y));
		result.push_back({ z0,z1 });
	}
	
	return result;
}

//возвращает отношение аденого пути к оптимальному
double FindRoute(int n) {
	/*vector<pair<double, double>> points = GetPoints(n);
	Graph G(n, n * (n - 1) / 2);
	for (auto p : points) {
		G.AddVertice(p.first, p.second);
	}*/

	Graph G(4,6);

	G.AddEdge(0, 1, 1);
	G.AddEdge(1, 2, 2);
	G.AddEdge(2, 3, 3);
	G.AddEdge(3, 0, 4);
	G.AddEdge(0, 2, 1);
	G.AddEdge(3, 1, 2);


	auto mst = G.FindMST();
	auto brute = G.BruteForce();
	return mst/brute;
}

//возвращает среднее время выполнения и стандартное отклонение
pair<double, double> Experiment(int n_points, int n_itterations = 20) {
	//здесь храним продолжительности прогонов
	vector<double> spen_time;
	for (int i = 0; i < n_itterations; i++) {
		spen_time.push_back(FindRoute(n_points));
	}

	return estimateStatistics(spen_time);
}

int main() {
	int n_experiments = 1;
	vector<pair<double,double>> times;
	for (int n_points = 6; n_points < 7; n_points++) {
		times.push_back(Experiment(n_points, 1));
	}
	return 0;
}
#include<vector>
#include<algorithm>
#include<random>
#include<iostream>
#include<math.h>
#include"Graph.h"
#include<time.h>
#include <numeric>
#include<iomanip>

const double M_PI = 3.141592653589793238462643383279502884;

using namespace std;

#pragma region Вспомогательные функции
//оценивает средее и отклонение массива
pair<double, double> estimateStatistics(vector<double> arr)
{
	double mean = accumulate(arr.begin(), arr.end(), 0.0) / arr.size();

	double sqDiff = 0;
	for (int i = 0; i < arr.size(); i++)
		sqDiff += (arr[i] - mean) * (arr[i] - mean);
	double var = sqDiff / arr.size();
	double std = sqrt(var);
	
	return { mean, std };
}

//Возвращает набор точек размера n
vector<pair<double, double>> GetPoints(int n){
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 gen(rd());	
	uniform_real_distribution<> dis(0.0, 1.0);
	
	vector<pair<double, double>> result;
	double x, y;
	for (int i = 0; i < n; i++) {
		x = dis(gen);
		y = dis(gen);
		double z0 = cos(2 * M_PI * x) * sqrt(-2* log(x));
		double z1 = cos(2 * M_PI * y) * sqrt(-2 * log(y));
		result.push_back({ z0,z1 });
	}
	
	return result;
}

//возвращает отношение найденого пути к оптимальному
double FindEfficiency(int n) {
	vector<pair<double, double>> points = GetPoints(n);
	Graph G(n, n * (n - 1) / 2);
	for (auto p : points) {
		G.AddVertice(p.first, p.second);
	}

	auto mst = G.FindMST();
	auto brute = G.BruteForce();
	return mst/brute;
}

//возвращает среднее время выполнения и стандартное отклонение
pair<double, double> Experiment(int n_points, int n_itterations = 20) {
	//здесь храним продолжительности прогонов
	vector<double> ratios;
	for (int i = 0; i < n_itterations; i++) {
		ratios.push_back(FindEfficiency(n_points));
	}
	return estimateStatistics(ratios);
}

//функция для вывода ячейки таблицы
template<typename T> void printElement(T t, const int& width)
{
	cout << left << setw(width) << setfill(' ') << t;
}

//Выводит стаститику в таблицу
void ShowStats(vector<pair<double, pair<double, double>>> stats) {
	printElement("N", 3);
	printElement("mean", 10);
	printElement("std", 10);
	cout << endl;

	for (auto s : stats) {
		printElement(s.first, 3);
		printElement(s.second.first, 10);
		printElement(s.second.second, 10);
		cout << endl;
	}
}
#pragma endregion

int main() {
	int n_experiments = 10;
	vector<pair<double,pair<double,double>>> stats;
	for (int n_points = 2; n_points < 11; n_points++) {
		stats.push_back({ n_points, Experiment(n_points, n_experiments) });
	}
	ShowStats(stats);
	return 0;
}
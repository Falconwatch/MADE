#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#define PI acos(-1.0)


using namespace std;

struct Point {
	double x;
	double y;

	//Возвращает расстояние от этой точки до интересующей нас
	double GetDistance(Point targetPoint) {
		return sqrt(pow(x - targetPoint.x, 2) + pow(y - targetPoint.y, 2));
	}

	//Возвращает угол между этой точкой и интересующей нас. эта точка - начало отсчёта
	double GetPolarAngle(Point targetPoint)
	{
		double x_rel = targetPoint.x - x;
		double y_rel = targetPoint.y - y;
		double res = atan2(y_rel, x_rel);
		if (res < 0) res += 2 * PI;
		return res;
	}

	//проверяет не та же ли это точка
	bool IsEqual(Point point) {
		return x == point.x && y == point.y;
	}
};


int FindBottomRightPoint(vector<Point> points)
{
	int found = 0;
	Point found_point;
	found_point = points[0];
	for (int i = 1; i < points.size(); i++) {
		if (points[i].y < found_point.y) {
			found_point = points[i];
			found = i;
		}
		else if (points[i].y == found_point.y) {
			if (points[i].x > found_point.x) {
				found_point = points[i];
				found = i;
			}
		}
	}
	return found;
}

double FindPerimetr(vector<Point> pointsSeq) {
	//считаем периметр
	double perimetr = 0;
	for (int i = 0; i < pointsSeq.size() - 1; i++) {
		double dist = sqrt(pow(pointsSeq[i].x - pointsSeq[i + 1].x, 2) + pow(pointsSeq[i].y - pointsSeq[i + 1].y, 2));
		perimetr += dist;
	}
	return perimetr;
}

int GetNearestPoint(vector<Point> pointsSeq, Point zeroPoint) {
	double nearest_point_angle = 99999999999;
	double nearest_point_distance = 99999999999;
	int nearest_point_index = -1;

	for (int i = 0; i < pointsSeq.size(); i++) {
		//мерим угол точки
		auto this_point_angle = zeroPoint.GetPolarAngle(pointsSeq[i]);
		auto this_point_distance = zeroPoint.GetDistance(pointsSeq[i]);
		if (this_point_angle < nearest_point_angle) {
			nearest_point_angle = this_point_angle;
			nearest_point_distance = zeroPoint.GetDistance(pointsSeq[i]);
			nearest_point_index = i;
		}
		//углы равны - мерим расстояние
		else if (this_point_angle == nearest_point_angle) {
			if (this_point_distance < nearest_point_distance) {
				nearest_point_angle = this_point_distance;
				nearest_point_distance = this_point_distance;
				nearest_point_index = i;
			}
		}
	}

	return nearest_point_index;
}



double FindShell(vector<Point> points) {

	vector<Point> answer_seq;

	//находим нижнюю-правую точку
	int bottom_right_index = FindBottomRightPoint(points);
	Point start_point = points[bottom_right_index];
	
	//добавляем её в ответ
	answer_seq.push_back(start_point);
	points.erase(points.begin() + bottom_right_index);
	
	//добавляем в ответ ещё одну точку - ближайшую к стартовой
	int nearest_point_index = GetNearestPoint(points, answer_seq[0]);
	answer_seq.push_back(points[nearest_point_index]);
	points.erase(points.begin() + nearest_point_index);
	
	//возвращаем стартовую точку и начинаем перебор
	points.push_back(start_point);
	
	Point cur_point;
	do{
		//нахожу точку ближаюшую к последней в ответе
		Point last_point = answer_seq[answer_seq.size() - 1];
		int nearest_point_index = GetNearestPoint(points, last_point);
		cur_point = points[nearest_point_index];
		//добавляю её в ответ и удаляю и спсика точек
		answer_seq.push_back(cur_point);
		points.erase(points.begin() + nearest_point_index);
	} while (!start_point.IsEqual(cur_point));
	
	//считаю периметр по заданной последовательности
	double perimetr = FindPerimetr(answer_seq);
	return perimetr;
}

int main() {
	cout.precision(9);
	vector<Point> points;

	//int n;
	//cin >> n;
	//double x, y;

	//for (int i = 0; i < n; i++) {
	//	cin >> x >> y;
	//	points.push_back({ x, y });
	//}

	points.push_back({ 1., 1. });
	points.push_back({ 2., 0. });
	points.push_back({ 0., 0. });
	points.push_back({ 0., 2. });
	points.push_back({ 2., 2. });

	double a = FindShell(points);

	cout << setprecision(15) << a;

	return 0;
}
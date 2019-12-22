#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#define PI acos(-1.0)


using namespace std;

class Point {
public:
	Point(double x, double y) : x(x), y(y) {};
	Point() {};

	//проверяет не та же ли это точка
	bool IsEqual(Point point) {
		return x == point.x && y == point.y;
	}
	//Возвращает расстояние от этой точки до интересующей нас
	double GetDistanceToPoint(Point target) {
		return sqrt(pow(x - target.x, 2) + pow(y - target.y, 2));
	}

	double GetPolarAngle(Point zeroPoint) {
		double x_rel = x - zeroPoint.GetX();
		double y_rel = y - zeroPoint.GetY();
		double res = atan2(y_rel, x_rel);
		if (res < 0) res += 2 * PI;
		return res;
	}

	double GetX() {
		return x;
	}

	double GetY() {
		return y;
	}

private:
	double x;
	double y;
};

class Vector {
public:
	Vector(Point start, Point end){
		start_ = start;
		end_ = end;
	}
	double GetLength() {
		return start_.GetDistanceToPoint(end_);
	}
	double GetX() { return end_.GetX() - start_.GetX(); }
	double GetY() { return end_.GetY() - start_.GetY(); }

private:
	Point start_;
	Point end_;
	
};


//Определяет угол между векторами
double GetAngleBetweenVectors(Vector v1, Vector v2) {
	double cos_alpha = (v1.GetX() * v2.GetX() + v1.GetY() * v2.GetY()) / (v1.GetLength() * v2.GetLength());
	double alpha = acos(cos_alpha);
	return alpha;
}
double GetAngleBetweenPoints(Point p1, Point p2, Point p3) {
	Vector v1(p1, p2);
	Vector v2(p2, p3);
	return GetAngleBetweenVectors(v1, v2);
}

int FindBottomRightPoint(vector<Point> points)
{
	int found = 0;
	Point found_point(0,0);
	found_point = points[0];
	for (int i = 1; i < points.size(); i++) {
		if (points[i].GetY() < found_point.GetY()) {
			found_point = points[i];
			found = i;
		}
		else if (points[i].GetY() == found_point.GetY()) {
			if (points[i].GetX() > found_point.GetX()) {
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
		//cout << pointsSeq[i].GetX() << ";" << pointsSeq[i].GetY() << endl;
		double dist = sqrt(pow(pointsSeq[i].GetX() - pointsSeq[i + 1].GetX(), 2) + pow(pointsSeq[i].GetY() - pointsSeq[i + 1].GetY(), 2));
		perimetr += dist;
	}
	return perimetr;
}

int GetNearestPoint(vector<Point> pointsSeq, Point lastPoint, Point prevPoint) {
	double nearest_point_angle = 99999999999;
	double nearest_point_distance = 99999999999;
	int nearest_point_index = -1;


	for (int i = 0; i < pointsSeq.size(); i++) {
		//мерим угол точки
		auto this_point_angle = GetAngleBetweenPoints(prevPoint, lastPoint, pointsSeq[i]);
		auto this_point_distance = lastPoint.GetDistanceToPoint(pointsSeq[i]);// GetDistanceBetweenPoints(lastPoint, pointsSeq[i]);
		if (this_point_angle < nearest_point_angle) {
			nearest_point_angle = this_point_angle;
			nearest_point_distance = this_point_distance;
			nearest_point_index = i;
		}
		//углы равны - мерим расстояние
		else if (this_point_angle == nearest_point_angle) {
			if (this_point_distance < nearest_point_distance) {
				nearest_point_angle = this_point_angle;
				nearest_point_distance = this_point_distance;
				nearest_point_index = i;
			}
		}
	}
	return nearest_point_index;
}

int GetNearestPoint(vector<Point> pointsSeq, Point lastPoint) {
	double nearest_point_angle = 99999999999;
	double nearest_point_distance = 99999999999;
	int nearest_point_index = -1;

	for (int i = 0; i < pointsSeq.size(); i++) {
		//мерим угол точки
		auto this_point_angle = pointsSeq[i].GetPolarAngle(lastPoint);
		auto this_point_distance = lastPoint.GetDistanceToPoint(pointsSeq[i]);
		if (this_point_angle < nearest_point_angle) {
			nearest_point_angle = this_point_angle;
			nearest_point_distance = this_point_distance;
			nearest_point_index = i;
		}
		//углы равны - мерим расстояние
		else if (this_point_angle == nearest_point_angle) {
			if (this_point_distance < nearest_point_distance) {
				nearest_point_angle = this_point_angle;
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
	
	
	Point cur_point(0, 0);
	do{
		//нахожу точку ближаюшую к последней в ответе
		Point last_point = answer_seq[answer_seq.size() - 1];
		Point prev_point = answer_seq[answer_seq.size() - 2];
		int nearest_point_index = GetNearestPoint(points, last_point, prev_point);
		cur_point = points[nearest_point_index];
		//добавляю её в ответ и удаляю их спсика точек
		answer_seq.push_back(cur_point);
		points.erase(points.begin() + nearest_point_index);
	} while (!start_point.IsEqual(cur_point));
	
	//считаю периметр по заданной последовательности
	double perimetr = FindPerimetr(answer_seq);
	return perimetr;
}

int main() {
	vector<Point> points;
	int n;
	cin >> n;
	double x, y;

	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points.push_back({ x, y });
	}

	cout << setprecision(9) << FindShell(points);
	return 0;
}
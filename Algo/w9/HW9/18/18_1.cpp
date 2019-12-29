//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<utility>
//#include <stdio.h>
//#include <math.h>
//#define PI acos(-1.0)
//
//
//using namespace std;
//
//struct Point {
//	float x;
//	float y;
//	float polarAngle;	
//};
//
//float GetPolarAngle(Point targetPoint,Point zeroPoint)
//{
//	float x = targetPoint.x - zeroPoint.x;
//	float y = targetPoint.y - zeroPoint.y;
//	double res = atan2(y, x);
//	if (res < 0) res += 2 * PI;
//	return res;
//}
//
//bool IsAngleOK(Point p1, Point p2, Point p3) {
//	float v1_x = p2.x - p1.x;
//	float v1_y = p2.y - p1.y;
//	float v2_x = p3.x - p2.x;
//	float v2_y = p3.y - p2.y;
//
//	return v1_x * v2_x + v1_y * v2_x > 0;
//}
//
// 
//bool ComparePointsByAngle(Point p1, Point p2)
//{
//	return (p1.polarAngle < p2.polarAngle);
//}
//
//
//
//
//int FindBottomRightPoint(vector<Point> points)
//{
//	int found = 0;
//	Point found_point;
//	found_point = points[0];
//	for (int i = 1; i < points.size(); i++) {
//		if (points[i].y < found_point.y) {
//			found_point = points[i];
//			found = i;
//		}
//		else if(points[i].y == found_point.y){
//			if (points[i].x > found_point.x) {
//				found_point = points[i];
//				found = i;
//			}
//		}
//	}
//	return found;
//}
//
//float FindShell(vector<Point> points) {
//
//	vector<Point> answer_seq;
//
//	//находим нижнюю-правую точку
//	int bottom_right_index = FindBottomRightPoint(points);
//	//для каждой точки считаем полярный угол относительно нижне йпарвой точки
//	for (int i = 0; i < points.size(); i++) {
//		points[i].polarAngle = GetPolarAngle(points[i], points[bottom_right_index]);
//	}
//
//	//сортируем все точки по по полярному углу
//	sort(points.begin(), points.end(), ComparePointsByAngle);
//
//	//добавялем в ответ точку p0 и точку p1 и удаялем их из списка точек
//	answer_seq.push_back(points[0]);
//	points.erase(points.begin());
//	answer_seq.push_back(points[0]);
//	points.erase(points.begin());
//
//	for (int i = 0; i < points.size(); i++) {
//		auto point_t = points[i];
//		auto point_pi = answer_seq[answer_seq.size()-1];
//		auto point_pi1 = answer_seq[answer_seq.size()-2];
//
//		auto ange_is_right = IsAngleOK(point_pi1, point_pi, point_t);
//		if (ange_is_right) {
//			answer_seq.erase(answer_seq.end() - 1);
//		}
//		answer_seq.push_back(point_t);
//	}
//	answer_seq.push_back(answer_seq[0]);
//
//	//считаем периметр
//	float perimetr = 0;
//	for (int i = 0; i < answer_seq.size()-1; i++) {
//		float dist = sqrt(pow(answer_seq[i].x - answer_seq[i + 1].x, 2) + pow(answer_seq[i].y - answer_seq[i + 1].y, 2));
//		perimetr += dist;
//	}
//
//	
//
//
//	
//
//	return perimetr;
//}
//
//int main() {
//	cout.precision(9);
//	vector<Point> points;
//	
//	int n;
//	cin >> n;
//	float x, y;
//	
//	for (int i = 0; i < n; i++) {
//		cin >> x >> y;
//		points.push_back({ x, y });
//	}
//	
//	/*points.push_back({ 1., 1. });
//	points.push_back({ 2., 1. });
//	points.push_back({ 0., 0. });*/
//
//	float a = FindShell(points);
//
//	cout << a;
//
//	return 0;
//}
#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;

struct Point {
	float x;
	float y;
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
		else if(points[i].y == found_point.y){
			if (points[i].x > found_point.x) {
				found_point = points[i];
				found = i;
			}
		}
	}
	return found;
}

float FindShell(vector<Point> points) {
	FindBottomRightPoint(points);
	return 0;
}

int main() {
	int n;
	cin >> n;
	float x, y;

	vector<Point> points;

	
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points.push_back({ x, y });
	}

	return 0;
}
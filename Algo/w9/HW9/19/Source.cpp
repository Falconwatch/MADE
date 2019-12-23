#include<iostream>
#include<vector>

using namespace std;

class Point {
public:
	Point() {};
	Point(float x, float y): x_(x), y_(y) {};

private:
	float x_;
	float y_;
};

class Rectangle {
public:
	Rectangle(float left, float bottom, float right, float top):
	left_(left), bottom_(bottom), right_(right), top_(top){};

	float left_;
	float bottom_;
	float right_;
	float top_;	
};


int main() {
	int n, m;
	
	vector<Point> points;
	cin >> n;
	for (int i = 0; i < n; i++) {
		float x, y;
		cin >> x >> y;
		points.push_back(Point(x, y));
	}

	vector<Rectangle> rectangles;
	cin >> m;
	for (int i = 0; i < m; i++) {
		float l, b, r, t;
		cin >> l >> b >> r >> t;
		rectangles.push_back(Rectangle(l,b,r,t));
	}

	return 0;
}
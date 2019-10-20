#include<iostream>

struct Point {
	int X;
	int Y;
	
	Point(int x = 0, int y=0): X(x), Y(y) {	}//X Y инициализируется до вызова тела конструктора
};

class IsLessByPoint {
public:
	IsLessByPoint(const Point& _leftmost): leftmost(_leftmost){}

	bool operator ()(const Point& l, Point& r) {
		return leftmost.X - l.X < leftmost.X - r.X;
	}
private:
	Point leftmost;
};

template <class T>
class IsLessDefault {
public:
	bool operator ()(const T& l, const T& r) {
		return l < r;
	}
private:
	Point leftmost;
};

bool IsLessByX(const Point& l, const Point& r) {
	return l.X < r.X;
}

template<class T>
bool IsLessByDefault(const T& l, const T& r) {
	return l < r;
}

template<class T, class IsLess>
void Sort(T* arr, int l, int r, IsLess isLess = IsLessByDefault())// (*isLess)(const T&, const T&)) {
{
	for (int i = l; i < r; i++)
		for (int j = l; j < r; j++)
		{
			if (isLess(arr[j + 1], arr[j]))
				std::swap(arr[j], arr[j+1]);
		}

}



int main() {
	Point arr[4] = { Point(1,2), Point(3,4), Point(9,3), Point(0, -3) };
	//Point* arr = new Point[4]{ Point(1,2), Point(3,4), Point(9,3), Point(0, -3)};
	Sort(arr, 1, 3, IsLessByPoint(arr[0]));
	for (int i = 0; i < 4; i++)
		std::cout << arr[i].X << ';' << arr[i].Y << ' | ';
	return 1;
}
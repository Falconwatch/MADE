#include <iostream>

class Heap {
	public:
		Heap();
		~Heap();

		void make_heap();

		void push_heap() {

		}

		int pop_heap();

		void sort_heap();

		void reverse();

		int getParrentIdx(int childIdx)
		{
			return int((childIdx - 1) / 2);
		}
		
		int getLeftChildIdx(int parrentIdx) {
			return 2 * parrentIdx + 1;
		}

		int getRightChildIdx(int parrentIdx) {
			return 2 * parrentIdx + 2;
		}

private:
	int* data;

};



int main() {
	int n;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	delete[] arr;
	return 0;
}
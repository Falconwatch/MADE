//#include "sort.h"

namespace mergesort {
//#include "sort.h"
	void merge(int* a, int left, int mid, int right) {
		int it1 = 0;
		int it2 = 0;
		int* result = new int[right - left];

		while (left + it1 < mid and mid + it2 < right) {
			if (a[left + it1] < a[mid + it2]) {
				result[it1 + it2] = a[left + it1];
				it1 += 1;
			}
			else {
				result[it1 + it2] = a[mid + it2];
				it2 += 1;
			}
		}

		while (left + it1 < mid) {
			result[it1 + it2] = a[left + it1];
			it1 += 1;
		}
		while (mid + it2 < right) {
			result[it1 + it2] = a[mid + it2];
			it2 += 1;
		}

		for (int i = 0; i < it1 + it2; i++)
			a[left + i] = result[i];
	}

	void mergeSortRecursive(int* a, int left, int right) {
		if (left + 1 >= right)
			return;
		int mid = (left + right) / 2;
		mergeSortRecursive(a, left, mid);
		mergeSortRecursive(a, mid, right);
		merge(a, left, mid, right);
	}

	void Sort(int* arr, int size) {
		int l = 0;
		int r = size - 1;
		mergeSortRecursive(arr, l, r);
	}
	
	
}

//int main() {
//	int* arr = new int[7]{ 1,5,2,3,9,0, 129 };
//	mergesort::Sort(arr, 7);
//	return 0;
//}
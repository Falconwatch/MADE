
namespace qsort {
	//#include "sort.h"

	void Swap(int& a, int& b)
	{
		int c(a); a = b; b = c;
	}

	int Partition(int* arr, int l, int r) {
		int v = arr[(l + r) / 2];
		int i = l;
		int j = r;
		while (i <= j) {
			while (arr[i] < v)
				i++;
			while (arr[j] > v)
				j--;
			if (i >= j)
				break;
			Swap(arr[i++], arr[j--]);
		}
		return j;
	}

	void QSort(int* arr, int l, int r) {
		if (l < r) {
			int q = Partition(arr, l, r);
			QSort(arr, l, q);
			QSort(arr, q + 1, r);
		}
	}


	void Sort(int* arr, int size) {
		int l = 0;
		int r = size - 1;
		QSort(arr, l, r);
	}

}

int main() {
	int* arr = new int[7]{ 1,5,2,3,9,0, 129 };
	qsort::Sort(arr, 7);
	return 0;
}
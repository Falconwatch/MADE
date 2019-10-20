/*
3_3. Количество инверсий.
Дана последовательность целых чисел из диапазона (-10^9 .. 10^9). Длина последовательности не больше 10^6. Числа записаны по одному в строке. Количество чисел не указано.  
Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
Указание: количество инверсий может быть больше 4*10^9 - используйте int64_t.
*/

#include <iostream>
#include <stdint.h>
#include <sstream>

using namespace std;

class Sequence {
public:
	Sequence(): last(0), size(0), data(nullptr) {
		Enlarge();
	}

	~Sequence() {
		delete[] data;
	}

	void AddElement(int element) {
		if (last == size)
			Enlarge();
		data[last] = element;
		last++;
	}

	int64_t countInversions() {
		int64_t a=ModifiedMergeSort(data, 0, last - 1);
		return a;
	}

	void Show() {
		for (int i = 0; i < last;i++) {
			cout << data[i];
		}
	}
	

private:
	int* data;
	int last;
	int size;

	void Enlarge() {
		int newSize; //new buffer size
		if (size > 0) {
			newSize = size * 2;
		}
		else {
			newSize = 8;
		}

		int* newData = new int[newSize];

		for (int i = 0; i < last; i++) {
			newData[i] = data[i];
		}

		if (data != nullptr) {
			delete[] data;
		}
		data = newData;
		size = newSize;
	}

	int64_t ModifiedMerge(int arr[], int l, int m, int r)
	{
		int64_t inverses = 0;
		int i, j, k;
		int n1 = m - l + 1;
		int n2 = r - m;

		/* create temp arrays */
		int* L = new int[n1];
		int* R = new int[n2];

		/* Copy data to temp arrays L[] and R[] */
		for (i = 0; i < n1; i++)
			L[i] = arr[l + i];
		for (j = 0; j < n2; j++)
			R[j] = arr[m + 1 + j];

		/* Merge the temp arrays back into arr[l..r]*/
		i = 0; // Initial index of first subarray 
		j = 0; // Initial index of second subarray 
		k = l; // Initial index of merged subarray 
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				inverses += n1 - i;
				arr[k] = R[j];
				j++;
			}
			k++;
		}

		/* Copy the remaining elements of L[], if there
		   are any */
		while (i < n1)
		{
			arr[k] = L[i];
			i++;
			k++;
		}

		/* Copy the remaining elements of R[], if there
		   are any */
		while (j < n2)
		{
			arr[k] = R[j];
			j++;
			k++;
		}

		delete[] L;
		delete[] R;
		return inverses;
	}

	/* l is for left index and r is right index of the
	   sub-array of arr to be sorted */
	int64_t ModifiedMergeSort(int arr[], int l, int r)
	{
		int64_t inv1 = 0, inv2 = 0, inv3 = 0;
		if (l < r)
		{
			// Same as (l+r)/2, but avoids overflow for 
			// large l and h 
			int m = l + (r - l) / 2;

			// Sort first and second halves 
			inv1 = ModifiedMergeSort(arr, l, m);
			inv2 = ModifiedMergeSort(arr, m + 1, r);

			inv3 = ModifiedMerge(arr, l, m, r);
		}
		return inv1 + inv2 + inv3;
	}
};

int main() {
	int64_t cnt = 0;
	Sequence* mySeq = new Sequence();
	string s;
	while (getline(cin, s)) {
		if (s.empty()) {
			break;
		}
		else {
			int a = std::stoi(s);
			mySeq->AddElement(a);
		}
	}

	cout << mySeq->countInversions();

	delete mySeq;
	return 0;
}
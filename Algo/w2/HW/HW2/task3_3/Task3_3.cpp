/*
3_3. ���������� ��������.
���� ������������������ ����� ����� �� ��������� (-10^9 .. 10^9). ����� ������������������ �� ������ 10^6. ����� �������� �� ������ � ������. ���������� ����� �� �������.  
����� ���������� ��������� n, � ����� �������� � ������� a = a[i]: i �� [0..n-1].
��������� ���������� ���������� ����� ��� �������� (i,j) �� [0..n-1], ��� (i < j � a[i] > a[j]).
��������: ���������� �������� ����� ���� ������ 4*10^9 - ����������� int64_t.
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
		return ModifiedMergeSort(data, 0, last - 1);
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
		int newSize; 
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

		int* L = new int[n1];
		int* R = new int[n2];

		for (i = 0; i < n1; i++)
			L[i] = arr[l + i];
		for (j = 0; j < n2; j++)
			R[j] = arr[m + 1 + j];

		i = 0; 
		j = 0;  
		k = l; 
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j]){
				arr[k] = L[i];
				i++;
			}
			else{
				inverses += n1 - i;
				arr[k] = R[j];
				j++;
			}
			k++;
		}

		while (i < n1){
			arr[k] = L[i];
			i++;
			k++;
		}

		while (j < n2){
			arr[k] = R[j];
			j++;
			k++;
		}

		delete[] L;
		delete[] R;
		return inverses;
	}

	int64_t ModifiedMergeSort(int arr[], int l, int r)
	{
		int64_t leftInverses = 0, rightInverses = 0, currentInverses = 0;
		if (l < r){
			// Same as (l+r)/2, but avoids overflow for 
			// large l and h 
			int m = l + (r - l) / 2;

			// Sort first and second halves 
			leftInverses= ModifiedMergeSort(arr, l, m);
			rightInverses = ModifiedMergeSort(arr, m + 1, r);

			currentInverses = ModifiedMerge(arr, l, m, r);
		}
		return leftInverses + rightInverses + currentInverses;
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
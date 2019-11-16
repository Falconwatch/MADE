/*
�����: �������� �����
4_4.
���� ��������������� ����� ����� n,k � ������ ����� ����� �� [0..10^9] ������� n. ��������� ����� k-� ���������� ����������. �.�. ���������� �����, ������� �� ������ �� ������� � �������� k (0..n-1) � ��������������� �������. �������� ������������� ��������.
���������� � �������������� ������: O(n). ��������� ������� ����� ������: O(n).
������� Partition ������� ������������� ������� ������� ����� ����������� � ����� �����������. �������� ��� ������ ������� �� ������ ������� � �����:
���������� ������� �������. ������� ������� �������� � ��������� ��������� �������.
�� ����� ������ Partition � ������ ������� ���������� ��������, �� ������� ��������. ����� ������������� ��������, ������ ������� ��������. � ����� ������� ����� ��������������� ��������. ��������� ��������� ����� �������.
�������� (������) i ��������� �� ������ ������ ���������, ������ ������� ��������.
�������� j ������ i, �������� j ��������� �� ������ ��������������� �������.
��� ���������. ��������������� �������, �� ������� ��������� j. ���� �� ������ ��������, �� �������� j.
���� �� �� ������ ��������, �� ������ a[i] � a[j] �������, �������� i � �������� j.
� ����� ������ ��������� ������ ������� � �������, �� ������� ��������� �������� i.

���������� ��������� ������ �������� �������� ���������� �������. ������� Partition ���������� ������� ������� ����� ����������� �� ����� ������� � ������.
*/

#include <iostream>
using namespace std;

//����� �������� ��������
int GetPivot(int min, int max) {
	int variable_index = rand() % (max - min + 1) + min;
	return variable_index;
}

class IsGrInt {
public:
	IsGrInt() {};
	bool operator ()(const int& l, int& r) {
		return l >= r;
	}
};

template <class T, class IsGr>
int Partition(T* arr, int l, int r, IsGr isgr) {
	int pivot_point = GetPivot(l, r);
	//������� ������� � ������
	if (l != r)
		std::swap(arr[pivot_point], arr[l]);
	//�������� ������ � �����
	T x = arr[l];
	int i = r+1;
	for (int j = r; j >= l; j--) {
		if (isgr(arr[j], x))
			std::swap(arr[--i], arr[j]);
	}
	return i;
}

template <class T, class IsGr>
int KStat(T* arr, int n, int k, IsGr isgr) {
	int left = 0;
	int right = n - 1;
	while (true) {
		int part = Partition(arr, left, right, isgr);
		if (part < k)
			left = part + 1;
		else
			if (part > k)
				right = part - 1;
			else
				return k;
	}
}

int main() {
	int n, k;
	cin >> n >> k;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int k_ind = KStat(arr, n, k, IsGrInt());
	cout << arr[k_ind];

	delete[] arr;
	return 0;
}
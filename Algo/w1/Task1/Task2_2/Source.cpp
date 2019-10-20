/*
�����: �������� ����� ��������� MADE-11
2_2. ������� ��������.
��� �������� ����� ������������ ������ ���������. �����, ������������� �� ���������� ����� ���� ����� ����� �� �����.
����� ������� ��� ���������� ����� ����� 1,2,3 ����� ������������� ������ �����, � ����������� �� ������� ����������.
((1+2)+3) -> 1+2 + 3+3 = 9
((1+3)+2) -> 1+3 + 4+2 = 10
((2+3)+1) -> 2+3 + 5+1 = 11
��������� �������� ���������, ������� ���������� ����������� �����, ����������� ��� ���������� ����� ��������� ������ �����.
������ ������� ������. ������� �������� n - ���������� �����. ����� �������� n ����� - �������� ����� (�������� ������� ����� �� ����������� 10^9, ����� ���� ����� �� ����������� 2*10^9).
������ �������� ������. ����������� ����� - ����������� �����.
in	out
5
5 2 3 4 6	45
5
3 7 6 1 9	56
*/

#include <iostream>
using namespace std;
class Heap {
	public:
		Heap(int* arr, int arr_size);
		~Heap();
		
		/*������� ���� �� ������*/
		void PrintData();
		/*����������� ����������� ������� � ���������� ��� ��������*/
		int PopMinimum();
		/*���������� �������� ������������ ��������*/
		int GetMinimum();
		/*���������� ������ ����*/
		int GetSize();
		/*��������� ������� � ����*/
		void AddElement(int element);

	private:
		int* data;
		int heapSize;
		/*�������� ������� �����*/
		void SiftUp(int i);
		/* �������� ������� ����*/
		void SiftDown(int i);
};

#pragma region ������������� ������� ����
Heap::Heap(int* arr, int arr_size): heapSize(0) {
	data = new int[arr_size];
	for (int i = 0; i < arr_size; i++) {
		AddElement(arr[i]);
	}
}

Heap::~Heap() {
	delete[] data;
}

void Heap::PrintData() {
	for (int i = 0; i < heapSize; i++) {
		std::cout << data[i] << " ";
	}
}

int Heap::PopMinimum() {
	int tmp = data[0];
	data[0] = data[heapSize - 1];
	heapSize--;
	SiftDown(0);
	return tmp;
}

int Heap::GetMinimum() {
	return data[0];
}

int Heap::GetSize() {
	return heapSize;
}

void Heap::AddElement(int element) {
	data[heapSize] = element;
	SiftUp(heapSize);
	heapSize++;
}

void Heap::SiftUp(int i) {
	while (data[i] < data[(i - 1) / 2]) {
		std::swap(data[i], data[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void Heap::SiftDown(int i) {
	while (2 * i + 1 < heapSize) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int j = left;
		if (right < heapSize and data[right] < data[left])
			j = right;
		if (data[i] <= data[j])
			break;
		std::swap(data[i], data[j]);
		i = j;
	}
}
#pragma endregion


int FindMinSum(Heap* heap) {
	int time = 0;
	int Sum = 0;
	while (heap->GetSize() > 1)
	{
		int min_elem = heap->PopMinimum();
		Sum = min_elem;
		int min_elem2 = heap->PopMinimum();
		Sum += min_elem2;
		heap->AddElement(Sum);
		time += Sum;
	}
	return time;
}

int main() {
	//��������� ����
	int n;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	//����� � ���� ��������� ������
	Heap* heap = new Heap(arr, n);
	//������� �����
	int minTime = FindMinSum(heap);
	std::cout << minTime;
	//������ �� �����
	delete[] arr;
	delete heap;
	return 0;
}
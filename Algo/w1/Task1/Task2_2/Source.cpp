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
		int* data_;
		int heap_size_;
		/*�������� ������� �����*/
		void SiftUp(int i);
		/* �������� ������� ����*/
		void SiftDown(int i);
};

#pragma region ������������� ������� ����
Heap::Heap(int* arr, int arr_size): heap_size_(0) {
	data_ = new int[arr_size];
	for (int i = 0; i < arr_size; i++) {
		AddElement(arr[i]);
	}
}

Heap::~Heap() {
	if (data_!=nullptr)	delete[] data_;
}

void Heap::PrintData() {
	for (int i = 0; i < heap_size_; i++) {
		std::cout << data_[i] << " ";
	}
}

int Heap::PopMinimum() {
	int tmp = data_[0];
	data_[0] = data_[heap_size_ - 1];
	heap_size_--;
	SiftDown(0);
	return tmp;
}

int Heap::GetMinimum() {
	return data_[0];
}

int Heap::GetSize() {
	return heap_size_;
}

void Heap::AddElement(int element) {
	data_[heap_size_] = element;
	SiftUp(heap_size_);
	heap_size_++;
}

void Heap::SiftUp(int i) {
	while (data_[i] < data_[(i - 1) / 2]) {
		std::swap(data_[i], data_[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void Heap::SiftDown(int i) {
	while (2 * i + 1 < heap_size_) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int j = left;
		if (right < heap_size_ and data_[right] < data_[left])
			j = right;
		if (data_[i] <= data_[j])
			break;
		std::swap(data_[i], data_[j]);
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
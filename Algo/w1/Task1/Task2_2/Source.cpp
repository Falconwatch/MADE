/*
Автор: Щербаков Игорь Андреевич MADE-11
2_2. Быстрое сложение.
Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
((1+2)+3) -> 1+2 + 3+3 = 9
((1+3)+2) -> 1+3 + 4+2 = 10
((2+3)+1) -> 2+3 + 5+1 = 11
Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел.
Формат входных данных. Вначале вводится n - количество чисел. Затем вводится n строк - значения чисел (значение каждого числа не превосходит 10^9, сумма всех чисел не превосходит 2*10^9).
Формат выходных данных. Натуральное число - минимальное время.
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
		
		/*Вывести кучу на печать*/
		void PrintData();
		/*Вытаскивает минимальный элемент и возвращает его значение*/
		int PopMinimum();
		/*Возвращает значение минимального значения*/
		int GetMinimum();
		/*Возвращает размер кучи*/
		int GetSize();
		/*Добавляет элемент в кучу*/
		void AddElement(int element);

	private:
		int* data_;
		int heap_size_;
		/*Просеять элемент вверх*/
		void SiftUp(int i);
		/* Просеять элемент вниз*/
		void SiftDown(int i);
};

#pragma region Имплементация методов кучи
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
	//Считываем ввод
	int n;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	//кладём в кучу считанный массив
	Heap* heap = new Heap(arr, n);
	//считаем время
	int minTime = FindMinSum(heap);
	std::cout << minTime;
	//читсим за собой
	delete[] arr;
	delete heap;
	return 0;
}
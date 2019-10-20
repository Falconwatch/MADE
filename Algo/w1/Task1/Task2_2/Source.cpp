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
		int* data;
		int heapSize;
		/*Просеять элемент вверх*/
		void SiftUp(int i);
		/* Просеять элемент вниз*/
		void SiftDown(int i);
};

#pragma region Имплементация методов кучи
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
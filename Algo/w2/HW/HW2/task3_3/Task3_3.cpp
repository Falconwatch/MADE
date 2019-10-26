/*
Автор: Щербаков Игорь MADE-11
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

#pragma region Динамический_массив

/*Свой динамический массив*/
class DynamicArr {
	public:
		DynamicArr();
		~DynamicArr();
		void Append(int value);
		int* GetArray();
		int GetSize();
	private:
		int* data_;
		int capacity_;
		int tail_;
		void Enlarge();
};

DynamicArr::DynamicArr(): capacity_(8), tail_(0){
	data_ = new int[capacity_];
}

DynamicArr::~DynamicArr() {
	if (data_ != nullptr) {
		delete[] data_;
	}
}

void DynamicArr::Append(int value) {
	if (tail_ == capacity_) {
		Enlarge();
	}
	data_[tail_] = value;
	tail_++;
}

void DynamicArr::Enlarge() {
	int new_capacity = capacity_ * 2;
	int* new_data = new int[new_capacity];
	for (int i = 0; i < tail_; i++) {
		new_data[i] = data_[i];
	}
	delete data_;
	data_ = new_data;
}

int* DynamicArr::GetArray() {
	return data_;
}

int DynamicArr::GetSize() {
	return tail_-1;
}
#pragma endregion

int64_t ModifiedMerge(int* arr, int l, int m, int r)
{
	int64_t inverses = 0;
	int i, j, k;
	int left_part_size = m - l + 1;
	int right_part_size = r - m;
	//создааём два подмассива
	int* L = new int[left_part_size];
	int* R = new int[right_part_size];
	//заполняем два подмассива
	for (i = 0; i < left_part_size; i++)
		L[i] = arr[l + i];
	for (j = 0; j < right_part_size; j++)
		R[j] = arr[m + 1 + j];

	//сливаем два подмассива
	i = 0;
	j = 0;
	k = l;
	while (i < left_part_size && j < right_part_size)
	{
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			//Считаем скоько чисел из левого массива прошли, сдвигая элемент из правого массива в начало
			inverses += left_part_size - i;
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	//сливаем  части в один массив
	while (i < left_part_size) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < right_part_size) {
		arr[k] = R[j];
		j++;
		k++;
	}
	//чистим за собой
	delete[] L;
	delete[] R;
	return inverses;
}

int64_t ModifiedMergeSort(int arr[], int l, int r)
{
	int64_t leftInverses = 0, rightInverses = 0, currentInverses = 0;
	if (l < r) {
		int m = l + (r - l) / 2;
		// Сортируем две части
		leftInverses = ModifiedMergeSort(arr, l, m);
		rightInverses = ModifiedMergeSort(arr, m + 1, r);
		//считаем количество инверсий в текущем мердже
		currentInverses = ModifiedMerge(arr, l, m, r);
	}
	//результат = инверсии в первой половине + инверсии во второй половине + инверсии при их слиянии
	return leftInverses + rightInverses + currentInverses;
}

int main() {
	int64_t cnt = 0;
	//Читаем ввод
	string s;
	int i;
	DynamicArr* arr = new DynamicArr();
	while (getline(cin, s)) {
		if (s.empty()) {
			break;
		}
		else {
			int a = std::stoi(s);
			arr->Append(a);
		}
	}
	//Считаем количество инверсий и выводим
	cout << ModifiedMergeSort(arr->GetArray(),0, arr->GetSize());
	cout << arr->GetArray();
	//cout << mySeq->CountInversions();
	//чистим
	delete arr;
	return 0;
}
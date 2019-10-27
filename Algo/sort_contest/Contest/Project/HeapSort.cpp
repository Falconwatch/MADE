

namespace HeapSort
{
	//#include "sort.h"	
	void Swap(int& a, int& b)
	{
		int c(a); a = b; b = c;
	}
	
#pragma region Heap

	class Heap {
	public:
		Heap(int* arr, int arr_size);
		~Heap();

		/*Вытаскивает минимальный элемент и возвращает его значение*/
		int PopMinimum();
		/*Возвращает размер кучи*/
		int GetSize();
	private:
		int* data_;
		int heap_size_;
		/*Просеять элемент вверх*/
		void SiftUp(int i);
		/* Просеять элемент вниз*/
		void SiftDown(int i);
	};

	Heap::Heap(int* arr, int arr_size) : heap_size_(arr_size) {
		data_ = new int[heap_size_];
		for (int i = 0; i < heap_size_; i++) {
			data_[i] = arr[i];
		}
		for (int i = arr_size / 2 - 1; i >= 0; i--) {
			SiftDown(i);
		}
	}

	Heap::~Heap() {
		if (data_ != nullptr)
			delete[] data_;
	}

	int Heap::PopMinimum() {
		int tmp = data_[0];
		data_[0] = data_[heap_size_ - 1];
		heap_size_--;
		SiftDown(0);
		return tmp;
	}

	int Heap::GetSize() {
		return heap_size_;
	}
	
	void Heap::SiftUp(int i) {
		while (data_[i] < data_[(i - 1) / 2]) {
			Swap(data_[i], data_[(i - 1) / 2]);
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
			Swap(data_[i], data_[j]);
			i = j;
		}
	}

#pragma endregion

	void Sort(int* arr, int size) {
		int l = 0;
		int r = size - 1;
		Heap* heap = new Heap(arr, size);
		for (int i = 0; i < size; i++) {
			arr[i] = heap->PopMinimum();
		}
		delete heap;
	}
}

//int main() {
//	int* arr = new int[7]{ 1,5,2,3,9,0, 129 };
//	HeapSort::Sort(arr, 7);
//	return 0;
//}

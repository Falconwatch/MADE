namespace HeapSort
{
	//#include "sort.h"	
	void Swap(int& a, int& b)
	{
		int c(a); a = b; b = c;
	}

	void SiftDown(int* arr, int i, int heap_size) {
		while (2 * i + 1 < heap_size) {
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			int j = left;
			if (right < heap_size and arr[right] > arr[left])
				j = right;
			if (arr[i] >= arr[j])
				break;
			Swap(arr[i], arr[j]);
			i = j;
		}
	}

	void BuildHeap(int* arr, int size) {
		for (int i = size / 2 - 1; i >= 0; i--) {
			SiftDown(arr, i, size);
		}
	}

	void Sort(int* arr, int size) {
		BuildHeap(arr, size);
		int heapSize = size;
		for (int i = 0; i <= size - 2; i++)
		{
			Swap(arr[0], arr[size - 1 - i]);
			heapSize--;
			SiftDown(arr, 0, heapSize);
		}
	}
}

//int main() {
//	int* arr = new int[7]{ 1,5,2,3,9,0, 129 };
//	HeapSort::Sort(arr, 7);
//	return 0;
//}

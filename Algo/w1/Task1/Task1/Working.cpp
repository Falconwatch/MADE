/**
Автор: Щербаков Игорь
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 100000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 ­ push front
a = 2 ­ pop front
a = 3 ­ push back
a = 4 ­ pop back
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b ­ ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “­1”.
Формат выходных данных.
Требуется напечатать YES ­ если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
Реализовать очередь с динамическим зацикленным буфером.
*/

#include <iostream>
using namespace std;

class Queue {
public:
	Queue();
	~Queue();
	/*Удалить первый элемент и вернуть его*/
	int PopFront();
	/*Добавить новый элемент в конец*/
	void PushBack(int val);
	/*Проверить, пуст ли массив*/
	bool IsEmpty();

private:
	int* data_;
	int size_;
	int head_; // номер первого элемента
	int tail_; // номер последнего элемента
	// увеличивает кол-во памяти
	void Enlarge();
};

Queue::Queue(): size_(0), head_(0), tail_(0), data_(nullptr) {
	Enlarge();
}

Queue::~Queue() {
	if (data_ != NULL) delete[] data_;
}

int Queue::PopFront() {
	if (head_ != tail_) {
		// очередь не пуста
		int val = data_[head_];
		if (head_ == size_ - 1) {
			head_ = 0;
		}
		else {
			head_++;
		}
		return val;
	}
	// очередь пуста
	return -1;
}

void Queue::PushBack(int val) {
	if ((tail_ + 1) % size_ == head_) {
		// память закончилась
		Enlarge();
		PushBack(val);
	}
	else {
		// добавляем следующий элемент
		data_[(tail_) % size_] = val;
		tail_ = (tail_ + 1) % size_;
	}
}

bool Queue::IsEmpty() {
	return head_ == tail_;
}

void Queue::Enlarge() {
	int newSize;
	if (size_ > 0) {
		newSize = size_ * 2;
		int* newData = new int[newSize];
		int j = 0;
		for (int i = head_; i < size_; i++) {
			if (i == tail_) {
				break;
			}
			newData[j++] = data_[i];
			if (i == size_ - 1) {
				i = -1;
			}
		}
		head_ = 0;
		tail_ = j;
		if (data_ != nullptr) {
			delete[] data_;
		}
		data_ = newData;
		size_ = newSize;
	}
	else {
		size_ = 8;
		data_ = new int[size_];
	}
}

int main(){
	Queue* q = new Queue();
	bool everything_is_ok = true;
	//чтение числа команд
	int n;
	std::cin >> n;
	//обработка команд
	for (int i = 0; i < n; i++) { 
		int a, b;
		std::cin >> a >> b;
		if (a == 2) {
			int v = q->PopFront();
			if (b != v) {
				everything_is_ok = false;
			}
		}
		else if (a == 3) {
			q->PushBack(b);
		}
	}
	//вывод результата проверки
	if (everything_is_ok) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	delete q;
	return 0;
}

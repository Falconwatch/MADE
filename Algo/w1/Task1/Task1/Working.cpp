/**
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
	int pop_front();

	/*Добавить новый элемент в конец*/
	void push_back(int val);

	/*Проверить, пуст ли массив*/
	bool isEmpty();

private:
	int* data; // массив с числами
	int size; // количество элементов, на которые выделена память

	int head; // номер первого элемента
	int tail; // номер последнего элемента

	// увеличивает кол-во памяти
	void enlarge();
};


Queue::Queue(){
	data = NULL;
	size = 0;

	head = 0;
	tail = 0;

	enlarge();
}

Queue::~Queue() {
	if (data != NULL) {
		delete[] data;
	}
}

int Queue::pop_front() {
	if (head != tail) {
		// очередь не пуста
		int val = data[head];

		if (head == size - 1) {
			head = 0;
		}
		else
		{
			head++;
		}

		return val;
	}
	// очередь пуста
	return -1;
}

void Queue::push_back(int val) {
	if ((tail + 1) % size == head) {
		// память закончилась
		enlarge();
		push_back(val);
	}
	else
	{
		// добавляем следующий элемент
		data[(tail) % size] = val;
		tail = (tail + 1) % size;
	}
}

bool Queue::isEmpty() {
	return head == tail;
}

void Queue::enlarge() {
	int newSize; //new buffer size
	if (size > 0) {
		newSize = size * 2;
	}
	else {
		newSize = 8;
	}

	int* newData = new int[newSize]; //new buffer

	int j = 0;
	for (int i = head; i < size; i++) {
		if (i == tail) {
			break;
		}
		newData[j++] = data[i];
		if (i == size - 1) {
			i = -1;
		}
	}
	head = 0;
	tail = j;

	if (data != NULL) {
		delete[] data;
	}
	data = newData;
	size = newSize;
}



int main(){
	Queue q;
	
	bool everything_is_ok = true;
	//чтение числа команд
	int n;
	std::cin >> n;
	//обработка команд
	for (int i = 0; i < n; i++) { 
		int a, b;
		std::cin >> a >> b;
		if (a == 2) {
			int v = q.pop_front();
			if (b != v) {
				everything_is_ok = false;
			}
		}
		if (a == 3) {
			q.push_back(b);
		}
	}

	//вывод результата проверки
	if (everything_is_ok) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	return 0;
}

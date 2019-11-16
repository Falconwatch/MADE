/*
MADE-11 Щербаков Игорь 
8_2

Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
1_2. Для разрешения коллизий используйте двойное хеширование.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
public:
	HashTable(): size_(8){
		table_.resize(size_);
	}

	bool Remove(string s) { 
		int k1 = FirstHashFunction(s);
		int k2 = SecondHashFunction(s);
		int i = k1;
		int j = 1;
		while (!table_[i].empty and table_[i].s != s) {
			i = (k1 + j * k2) % size_;
			if (i == k1)
				break;
			++j;
		}

		if (!table_[i].empty and table_[i].s == s and !table_[i].removed) {
			table_[i].removed = true;
			++deleted_;
			return true;
		}
		else
			return false;
	}

	int Add(string s) { // вставляет строку в таблицу
		int hash1 = FirstHashFunction(s);
		int hash2 = SecondHashFunction(s);
		int i = hash1;
		int j = 1;
		while (!table_[i].empty and table_[i].s != s) {
			i = (hash1 + j * hash2) % size_;
			++j;
		}
		if (table_[i].empty) {
			table_[i].s = s;
			table_[i].empty = false;
			++filled_;
			if (filled_ >= 3 * size_ / 4)
				Rehash_(size_ * 2);
			return 1;
		}
		else {
			if (table_[i].removed == true) {
				table_[i].removed = false;
				--deleted_;
				return 1;
			}
		}
		return 0;
	}

	bool Find(string s) {
		int hash1 = FirstHashFunction(s);
		int hash2 = SecondHashFunction(s);
		int i = hash1;
		int j = 1;
		while (!table_[i].empty and table_[i].s != s) {
			i = (hash1 + j * hash2) % size_;
			if (i == hash1)
				break;
			++j;
		}

		if (!table_[i].empty and table_[i].s == s and !table_[i].removed)
			return true;
		else
			return false;
	}

private:
	struct TreeNode { // ячейка таблицы;
		bool empty = true; // хранится ли в данной ячейка строка (возможно, удаленная);
		bool removed = false; // удалена ли строка, находящаяся в данной ячейке;
		string s;
	};

	int size_;
	int filled_ = 0; // кол-во ячеек с записанной информацией;
	int deleted_ = 0; // кол-во удаленных ячеек, т.е. помеченных как deleted;

	vector<TreeNode> table_; // буфер хеш-таблицы;
	vector<int> primes_ = { 7, 79, 379, 3847, 62201, 382871, 2972969 }; // простые числа, которые при необходимости заменят a_ - число, использующееся в хеш-функции;

	int a_ = primes_[trunc(log10(8))]; // число a_ выбирается из простых так, чтобы по разрядности совпадать с размером буфера;

	int FirstHashFunction(string value) { // первая хеш-функция;
		int res = 0;
		for (int i = value.size() - 1; i >= 0; --i)
			res = ((res + value[i]) * a_) % size_;
		return res;
	}

	int SecondHashFunction(string value) { // вторая хеш-функция;
		int res = 0;
		for (int i = 0; i < value.size(); ++i)
			res = ((res + value[i]) * a_) % size_;
		if (res % 2)
			return res;
		else
			return res + 1;
	}

	void Rehash_(int new_size) { // перехеширование;
		vector<TreeNode> new_list;
		new_list.resize(new_size);
		size_ = new_size;
		a_ = primes_[trunc(log10(new_size))];
		filled_ -= deleted_;
		deleted_ = 0;
		for (int h = 0; h < table_.size(); ++h) {
			if (!table_[h].empty and !table_[h].removed) {
				int k1 = FirstHashFunction(table_[h].s);
				int k2 = SecondHashFunction(table_[h].s);
				int i = k1;
				int j = 1;
				while (!new_list[i].empty) {
					i = (k1 + j * k2) % size_;
					++j;
				}
				new_list[i].s = table_[h].s;
				new_list[i].empty = false;
			}
		}

		table_ = move(new_list);
	}

};

int main(){
	HashTable* ht = new HashTable();
	char command = ' ';
	std::string value;
	while (std::cin >> command >> value) {
		switch (command) {
		case '?':
			std::cout << (ht->Find(value) ? "OK" : "FAIL") << std::endl;
			break;
		case '+':
			std::cout << (ht->Add(value) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (ht->Remove(value) ? "OK" : "FAIL") << std::endl;
			break;
		}
	}

	delete ht;
	return 0;
}
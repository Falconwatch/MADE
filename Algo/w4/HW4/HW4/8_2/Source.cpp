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

using namespace std;

struct TreeNode {
	bool empty = true;
	bool removed = false;
	string s;
};

class HashTable {
public:
	HashTable();
	bool Remove(string value);
	bool Add(string value);
	bool Find(string value);
private:
	vector<TreeNode> buffer_;
	int buffer_size_;
	int filled_ = 0; 
	int deleted_ = 0; 
	int a_ = 1291;	

	int FirstHashFunction(string value);
	int SecondHashFunction(string value);	   
	void Rehash_(int new_size);
};

HashTable::HashTable() : buffer_size_(8), deleted_(0), filled_(0) {
	buffer_.resize(buffer_size_);
}

bool HashTable::Remove(string value) {
	int hash1 = FirstHashFunction(value);
	int hash2 = SecondHashFunction(value);
	int i = hash1;
	int j = 1;
	while (!buffer_[i].empty and buffer_[i].s != value) {
		i = (hash1 + j * hash2) % buffer_size_;
		if (i == hash1)
			break;
		j++;
	}

	if (!buffer_[i].empty and buffer_[i].s == value and !buffer_[i].removed) {
		buffer_[i].removed = true;
		deleted_++;
		return true;
	}
	else
		return false;
}

bool HashTable::Add(string value) { // вставляет строку в таблицу
	int hash1 = FirstHashFunction(value);
	int hash2 = SecondHashFunction(value);
	int i = hash1;
	int j = 1;
	while (!buffer_[i].empty and buffer_[i].s != value) {
		i = (hash1 + j * hash2) % buffer_size_;
		j++;
	}
	if (buffer_[i].empty) {
		buffer_[i].s = value;
		buffer_[i].empty = false;
		filled_++;
		if (filled_ >= 3 * buffer_size_ / 4)
			Rehash_(buffer_size_ * 2);
		return true;
	}
	else {
		if (buffer_[i].removed == true) {
			buffer_[i].removed = false;
			deleted_--;;
			return true;
		}
	}
	return false;
}

bool HashTable::Find(string value) {
	int hash1 = FirstHashFunction(value);
	int hash2 = SecondHashFunction(value);
	int i = hash1;
	int j = 1;
	while (!buffer_[i].empty and buffer_[i].s != value) {
		i = (hash1 + j * hash2) % buffer_size_;
		if (i == hash1)
			break;
		j++;
	}

	if (!buffer_[i].empty and buffer_[i].s == value and !buffer_[i].removed)
		return true;
	else
		return false;
}

int HashTable::FirstHashFunction(string value) {
	int hash = 0;
	for (int i = value.size() - 1; i >= 0; i--)
		hash = ((hash + value[i]) * a_) % buffer_size_;
	return hash;
}

int HashTable::SecondHashFunction(string value) {
	int hash = 0;
	for (int i = 0; i < value.size(); i++)
		hash = ((hash + value[i]) * a_) % buffer_size_;
	if (hash % 2)
		return hash;
	else
		return hash + 1;
}

void HashTable::Rehash_(int new_size) {
	vector<TreeNode> new_list;
	new_list.resize(new_size);
	buffer_size_ = new_size;
	filled_ -= deleted_;
	deleted_ = 0;
	for (int h = 0; h < buffer_.size(); h++) {
		if (!buffer_[h].empty and !buffer_[h].removed) {
			int hash1 = FirstHashFunction(buffer_[h].s);
			int hash2 = SecondHashFunction(buffer_[h].s);
			int i = hash1;
			int j = 1;
			while (!new_list[i].empty) {
				i = (hash1 + j * hash2) % buffer_size_;
				j++;
			}
			new_list[i].s = buffer_[h].s;
			new_list[i].empty = false;
		}
	}

	buffer_ = move(new_list);
}

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
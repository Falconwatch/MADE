/*
MADE-11 �������� ����� 
8_2

���������� ��������� ������ ���� ���������� ����� �� ������ ������������ ���-������� � �������� ����������. �������� ������ �������� � ������� �� �������� ��������� ����.
���-������� ������ ������ ���� ����������� � ������� ���������� �������� ���������� ������� �������.
��������� ������ ������� ������ ���� ������ 8-��. ��������������� ���������� ��� ���������� ��������� � ������, ����� ����������� ���������� ������� ��������� 3/4.
��������� ������ ������ ������������ �������� ���������� ������ � ���������, �������� ������ �� ��������� � �������� �������������� ������ ������ ���������.
1_1. ��� ���������� �������� ����������� ������������ ������������. i-�� �����
g(k, i)=g(k, i-1) + i (mod m). m - ������� ������.
1_2. ��� ���������� �������� ����������� ������� �����������.
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

	int Add(string s) { // ��������� ������ � �������
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
	struct TreeNode { // ������ �������;
		bool empty = true; // �������� �� � ������ ������ ������ (��������, ���������);
		bool removed = false; // ������� �� ������, ����������� � ������ ������;
		string s;
	};

	int size_;
	int filled_ = 0; // ���-�� ����� � ���������� �����������;
	int deleted_ = 0; // ���-�� ��������� �����, �.�. ���������� ��� deleted;

	vector<TreeNode> table_; // ����� ���-�������;
	vector<int> primes_ = { 7, 79, 379, 3847, 62201, 382871, 2972969 }; // ������� �����, ������� ��� ������������� ������� a_ - �����, �������������� � ���-�������;

	int a_ = primes_[trunc(log10(8))]; // ����� a_ ���������� �� ������� ���, ����� �� ����������� ��������� � �������� ������;

	int FirstHashFunction(string value) { // ������ ���-�������;
		int res = 0;
		for (int i = value.size() - 1; i >= 0; --i)
			res = ((res + value[i]) * a_) % size_;
		return res;
	}

	int SecondHashFunction(string value) { // ������ ���-�������;
		int res = 0;
		for (int i = 0; i < value.size(); ++i)
			res = ((res + value[i]) * a_) % size_;
		if (res % 2)
			return res;
		else
			return res + 1;
	}

	void Rehash_(int new_size) { // ���������������;
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
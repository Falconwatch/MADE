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

using namespace std;

struct HashTableNode {
	string data_;
	HashTableNode* next = nullptr;
	HashTableNode(string key) : data_(std::move(key)) {}
};

class HashTable {
public:
	HashTable();
	~HashTable();
	bool Has(const string& value);
	bool Add(const string& value);
	bool Remove(const string& value);
private:
	int Hash1(const string& value);
	int Hash2(const string& value);
	std::vector<HashTableNode*> table_;
};

HashTable::HashTable(): table_(8, nullptr) {};

HashTable::~HashTable() {
	for (HashTableNode* head : table_) {
		while (head) {
			HashTableNode* next = head->next;
			delete head;
			head = next;
		}
	}
};

bool HashTable::Has(const string& value) {
	
	const size_t hash = value[0] % table_.size();
	for (auto head = table_[hash]; head != nullptr; head = head->next) {
		if (head->data_ == value) {
			return true;
		}
	}
	return false;
}

bool HashTable::Add(const string& value) {
	const size_t hash = value[0] % table_.size();
	for (auto head = table_[hash]; head != nullptr; head = head->next) {
		if (head->data_ == value) {
			return false;
		}
	}
	HashTableNode* new_node = new HashTableNode(value);
	new_node->next = table_[hash];
	table_[hash] = new_node;
	return true;
}

bool HashTable::Remove(const string& value) {

	const size_t hash = value[0] % table_.size();
	HashTableNode*& head = table_[hash];
	if (!head) return false;
	if (head->data_ == value) {
		HashTableNode* to_delete = head;
		head = head->next;
		delete to_delete;
		return true;
	}
	HashTableNode* parent = head;
	for (; parent->next != nullptr; parent = parent->next) {
		if (parent->next->data_ == value) {
			HashTableNode* to_delete = parent->next;
			parent->next = parent->next->next;
			delete to_delete;
			return true;
		}
	}
	return false;
}


int main(){
	HashTable* ht = new HashTable();
	char command = ' ';
	std::string value;
	while (std::cin >> command >> value) {
		switch (command) {
		case '?':
			std::cout << (ht->Has(value) ? "OK" : "FAIL") << std::endl;
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
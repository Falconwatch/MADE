/*
Напишите две функции для создания архива из одного файла и извлечения файла из архива.


// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);
 где:
typedef unsigned char byte;

struct IInputStream {
	// Возвращает false, если поток закончился
	bool Read(byte& value) = 0;
};

struct IOutputStream {
	void Write(byte value) = 0;
};

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит скоринг зависящий от соотношения размера сжатого файла и исходного.
*/


/*
#include "Huffman.h"
#include <map>
#include <list>

using namespace std;

class Node
{
public:
	int weight;
	byte value;
	Node* left, * right;

	Node() { left = right = NULL; }

	Node(Node* L, Node* R)
	{
		left = L;
		right = R;
		weight = L->weight + R->weight;
	}
};

struct NodeCompare
{
	bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};

static void copyStream(IInputStream& input, IOutputStream& output)
{
	byte value;
	while (input.Read(value))
	{
		output.Write(value);
	}
}

//vector<bool> code;
//map<char, vector<bool> > table;


void BuildTable(Node* root, vector<bool> code)
{
	if (root->left != NULL)
	{
		code.push_back(0);
		BuildTable(root->left, code);
	}

	if (root->right != NULL)
	{
		code.push_back(1);
		BuildTable(root->right, code);
	}

	if (root->c) table[root->c] = code;

	code.pop_back();
}

void Encode(IInputStream& original, IOutputStream& compressed)
{
	//copyStream(original, compressed);

	//сохраняем частоты байт
	std::vector<int> frequencies(256, 0);
	byte value;
	while (input.Read(value))
	{
		frequencies[value]++;
		output.Write(value);
	}

	////// записываем начальные узлы в список list
	list<Node*> node_list;
	for (std::vector<int>::size_type i = 0; i != frequencies.size(); i++) {
		Node* node = new Node();
		node->value = (byte)i;
		node->weight = frequencies[i];
		node_list.push_back(node);
	}

	//создаём дерево
	while (node_list.size() != 1)
	{
		node_list.sort(NodeCompare());

		Node* SonL = node_list.front();
		node_list.pop_front();
		Node* SonR = node_list.front();
		node_list.pop_front();

		Node* parent = new Node(SonL, SonR);
		node_list.push_back(parent);
	}

	//сохраняем ссылку на вершину дерева
	Node* root = node_list.front();

	//таблица кодов
	vector<vector<int>> codes_table(256, nullptr);


}

void Decode(IInputStream& compressed, IOutputStream& original)
{
	copyStream(compressed, original);
}
*/
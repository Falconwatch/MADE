#include <vector>
#include <sstream> 
#include <list>


using namespace std;

class Node {
public:
	int weight;
	char value;
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
	bool operator()(const Node* l, const Node* r) const { return l->weight < r->weight; }
};



void Encode(vector<char> original, vector<char> compressed)
{

	//сохраняем частоты байт
	//std::vector<int> frequencies(256, 0);
	//char* value;
	//while (original.read(value, 1))
	//{
	//	frequencies[value]++;
	//}

	//тестовое решение
	std::vector<int> frequencies(256, 0);
	for (std::vector<int>::size_type i = 0; i != original.size(); i++) {
		char value = original[i];
		frequencies[value]++;
	}


	////// записываем начальные узлы в список list
	list<Node*> node_list;
	for (std::vector<int>::size_type i = 0; i != frequencies.size(); i++) {
		Node* node = new Node();
		node->value = (char)i;
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


int main() {

	std::string str = "hello";
	std::vector<char> data(str.begin(), str.end());

	std::vector<char> compressed_data;

	Encode(data, compressed_data);

	return 0;
}
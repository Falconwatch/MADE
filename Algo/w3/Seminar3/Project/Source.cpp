#include <iostream>
using namespace std;

class Tree {
public:
	void Add(int k);
	void Delete(int k) {
		//�����
		//�������
		//�������� �����
		//���������� ��������� ������
	}
	bool Has(int k);

	void Split(TreapNode* root, int key, TreapNode*& left, TreapNode*& right) {
		if (root == nullptr) {
			left = right = nullptr;
		}
		if (key > root->key_) {
			TreapNode* rightLeft = nullptr;
			TreapNode* rightRight = nullptr;
			Split(root->rightChild_, key, rightLeft, rightRight);
			left = root;
			left->rightChild_ = rightLeft;
			right = rightRight;

		}
		else {
			Split(root->leftChild_, key, left, root->leftChild_);
				right = root;
		
		}
	}
private:
	TreapNode* root_;
};

struct TreapNode {
public:
	int key_;
	int p_;
	TreapNode* leftChild_;
	TreapNode* rightChild_;
};

void Merge(TreapNode* left, TreapNode* right) {
	if (right->p_ > left->p_)
	{

	}
}




int main() {
	////������ �� ����� �����
	//int i;
	//while (cin >> i) {

	//}

	return 0;
}
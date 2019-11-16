/*
7_2 Щербаков ИГорь MADE-11

В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n) амортизационно.
В реализации используйте сплей деревья.
*/

#include <functional>
#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
	Node<T>* left_;
	Node<T>* right_;
	Node<T>* parent_;
	Node<T>* next_;
	Node<T>* prev_;
	T data_;

	size_t size_;

	Node() {
		left_ = nullptr;
		right_ = nullptr;
		parent_ = nullptr;
		next_ = nullptr;
		prev_ = nullptr;
		size_ = 1;
	}

	Node(const T& a) : Node() {
		data_ = a;
	}
};

template <typename T>
class SplayTree {
public:
	Node<T>* root_;

	SplayTree() {
		root_ = nullptr;
	}

	SplayTree(Node<T>* root) {
		this->root_ = root;
	}

	~SplayTree() {
		DeleteSubtree(root_);
	}

	void DeleteSubtree(Node<T>* cur) {
		if (cur == nullptr) return;
		if (cur->left_ == nullptr && cur->right_ == nullptr) {
			delete cur;
			return;
		}

		DeleteSubtree(cur->left_);
		DeleteSubtree(cur->right_);
		delete cur;
	}

	int Insert(const T& data) {
		if (root_ == nullptr) {
			root_ = new Node<T>(data);
			return 0;
		}

		Node<T>* res = Find(data);

		if (data > res->data_) {
			Node<T>* new_node = new Node<T>(data);
			res->right_ = new_node;
			res->right_->parent_ = res;

			if (res->next_ != nullptr)
				res->next_->prev_ = res->right_;
			res->right_->next_ = res->next_;

			res->next_ = res->right_;
			res->right_->prev_ = res;

			Splay(res->right_);
			return GetSize(root_->right_);
		}
		else {
			Node<T>* new_node = new Node<T>(data);
			res->left_ = new_node;
			res->left_->parent_ = res;

			if (res->prev_ != nullptr)
				res->prev_->next_ = res->left_;
			res->left_->prev_ = res->prev_;

			res->prev_ = res->left_;
			res->left_->next_ = res;

			Splay(res->left_);
			return GetSize(root_->right_);
		}
	}

	void Remove(int position) {
		Node<T>* res = FindByPosition(position);

		Node<T>* tmp = res->prev_;
		if (res->prev_ != nullptr)
			res->prev_->next_ = res->next_;
		if (res->next_ != nullptr)
			res->next_->prev_ = tmp;

		SplayTree<T>* R = Split(res);

		Node<T>* root_old = root_;
		root_ = root_old->left_;
		delete root_old;

		if (root_ != nullptr)
			root_->parent_ = nullptr;
		Join(R);
	}

	Node<T>* GetPrev(const T& data) {
		Node<T>* found = Find(data);
		if (found == nullptr)
			return nullptr;
		Node<T>* result = nullptr;

		if (found->data_ < data) {
			result = found;
		}
		else if (found->data_ >= data) {
			result = found->prev_;
		}
		return result;
	}

	Node<T>* FindByPosition(int position) {
		if (position > GetSize()) return nullptr;
		return FindByPosition(position, root_);
	}

	int GetSize() {
		return GetSize(root_);
	}

private:
	Node<T>* FindByPosition(int order, Node<T>* cur) {

		if (order == GetSize(cur->right_)) return cur;
		if (order < GetSize(cur->right_)) {
			return FindByPosition(order, cur->right_);
		}
		else {
			return FindByPosition(order - GetSize(cur->right_) - 1, cur->left_);
		}
	}

	int GetSize(Node<T>* cur) {
		return (cur == nullptr) ? 0 : cur->size_;
	}

	void RepairSize(Node<T>* cur) {
		if (cur != nullptr) {
			cur->size_ = 1 + GetSize(cur->left_) + GetSize(cur->right_);
		}
	}

	Node<T>* Find(const T& data) {
		if (root_ == nullptr) return nullptr;

		Node<T>* cur = root_;
		while (true) {
			if (data > cur->data_) {
				if (cur->right_ == nullptr) break;
				else cur = cur->right_;
			}
			else if (data < cur->data_) {
				if (cur->left_ == nullptr) break;
				else cur = cur->left_;
			}
			else {
				break;
			}
		}

		return cur;
	}

	void Zig(Node<T>* cur) {
		if (cur == nullptr) return;
		if (cur->parent_ == nullptr) {
			RepairSize(cur);
			return;
		}
		if (cur->parent_->parent_) {
			if (cur->parent_->parent_->left_ == cur->parent_) {
				cur->parent_->parent_->left_ = cur;
			}
			else {
				cur->parent_->parent_->right_ = cur;
			}
		}

		if (cur->parent_->left_ == cur) {
			Node<T>* P = cur->parent_;
			Node<T>* R = cur->right_;
			cur->parent_ = P->parent_;
			cur->right_ = P;
			P->parent_ = cur;
			P->left_ = R;
			if (R) {
				R->parent_ = P;
			}
		}

		else if (cur->parent_->right_ == cur) {
			Node<T>* P = cur->parent_;
			Node<T>* L = cur->left_;
			cur->parent_ = P->parent_;
			cur->left_ = P;
			P->parent_ = cur;
			P->right_ = L;
			if (L) {
				L->parent_ = P;
			}
		}

		if (cur->parent_ == nullptr) {
			root_ = cur;
		}

		RepairSize(cur->left_);
		RepairSize(cur->right_);
		RepairSize(cur);
	}

	void Splay(Node<T>* cur) {
		if (cur == nullptr) return;
		if (cur->parent_ == nullptr) {
			RepairSize(cur);
			root_ = cur;
			return;
		}
		if (cur->parent_->parent_ == nullptr) {
			Zig(cur);
			root_ = cur;
			return;
		}
		Zig(cur->parent_);
		Zig(cur);
		Splay(cur);
	}

	SplayTree<T>* Split(Node<T>* res) {
		Splay(res);
		Node<T>* R = root_->right_;
		root_->right_ = nullptr;
		if (R != nullptr)
			R->parent_ = nullptr;
		RepairSize(root_);
		return new SplayTree<T>(R);
	}

	void Join(SplayTree<T>* right_tree) {
		if (root_ == nullptr && right_tree->root_ == nullptr) {
			delete right_tree;
			return;
		}
		Splay(GetMaxNode());

		if (root_ != nullptr) {
			root_->right_ = right_tree->root_;

			if (root_->right_ != nullptr)
				root_->right_->parent_ = root_;
		}
		else {
			root_ = right_tree->root_;
			root_->parent_ = nullptr;
		}
		RepairSize(root_);

		right_tree->root_ = nullptr;
		delete right_tree;
	}

	Node<T>* GetMaxNode() {
		Node<T>* cur = root_;
		if (cur == nullptr) return nullptr;
		while (cur->right_ != nullptr) {
			cur = cur->right_;
		}
		return cur;
	}
};


int main()
{
	SplayTree<int>* st = new SplayTree<int>();

	int n;
	std::cin >> n;

	for (int i = 0; i < n; i++) {
		int k, r;
		std::cin >> k >> r;
		if (!(k < 1 || r < 0)) {
			if (k == 1)
				std::cout << st->Insert(r) << std::endl;
			if (k == 2)
				st->Remove(r);
		}
	}
	delete st;
	return 0;
}
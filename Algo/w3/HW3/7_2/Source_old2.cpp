/*
В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n) амортизационно.
В реализации используйте сплей деревья.
*/

#include <functional>
#include <iostream>

using namespace std;

template <typename T>
struct Node {
	Node<T>* left_;
	Node<T>* right_;
	Node<T>* parent_;
	Node<T>* next_;
	Node<T>* prev_;
	T key;

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
		key = a;
	}

	Node(const Node& b) = delete;
};

template <typename T>
struct SplayTree {
	Node<T>* root_;

	SplayTree() {
		root_ = nullptr;
	}

	explicit SplayTree(Node<T>* root) {
		this->root_ = root;
	}

	SplayTree(const SplayTree& b) = delete;

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

	int Insert(const T& key) {
		if (root_ == nullptr) {
			root_ = new Node<T>(key);
			return 0;
		}

		Node<T>* res = Find(key);

		if (res->key == key) return 0;
		if (key > res->key) {
			res->right_ = new Node<T>(key);
			res->right_->parent_ = res;

			if (res->next_ != nullptr)
				res->next_->prev_ = res->right_;
			res->right_->next_ = res->next_;

			res->next_ = res->right_;
			res->right_->prev_ = res;

			Splay(res->right_);
			return 0;
		}
		else {
			res->left_ = new Node<T>(key);
			res->left_->parent_ = res;

			if (res->prev_ != nullptr)
				res->prev_->next_ = res->left_;
			res->left_->prev_ = res->prev_;

			res->prev_ = res->left_;
			res->left_->next_ = res;

			Splay(res->left_);
			return 0;
		}

	}

	void Remove(const T& key) {
		Node<T>* res = find_by_order(key);

		if (res == nullptr || res->key != key) return;

		Node<T>* tmp = res->prev_;
		if (res->prev_ != nullptr)
			res->prev_->next_ = res->next_;
		if (res->next_ != nullptr)
			res->next_->prev_ = tmp;

		SplayTree<T>* R = Split(key);

		Node<T>* wasRoot = root_;
		root_ = wasRoot->left_;
		delete wasRoot;

		if (root_ != nullptr)
			root_->parent_ = nullptr;


		Join(R);

	}

	bool Exists(const T& key) {
		Node<T>* res = Find(key);

		if (res == nullptr || res->key != key)
			return 0;
		else
			return 1;
	}

	Node<T>* GetNext(const T& key) {
		Node<T>* res = Find(key);

		if (res == nullptr)
			return nullptr;

		Node<T>* ans = nullptr;

		if (res->key > key) {
			ans = res;
		}
		else if (res->key <= key) {
			ans = res->next_;
		}

		return ans;
	}

	Node<T>* GetPrev(const T& key) {
		Node<T>* res = Find(key);

		if (res == nullptr)
			return nullptr;

		Node<T>* ans = nullptr;

		if (res->key < key) {
			ans = res;
		}
		else if (res->key >= key) {
			ans = res->prev_;
		}

		return ans;
	}

	Node<T>* FindByPosition(size_t order) {
		if (order > size()) return nullptr;
		return find_by_order(order, root_);
	}

	Node<T>* find_by_key(const T& key) {
		Node<T>* res = Find(key);

		if (res->key != key) return nullptr;
		else return res;
	}

	size_t size() {
		return size(root_);
	}

	void Inorder(Node<T>* cur)
	{
		if (!cur) return;
		Inorder(cur->left_);
		printf("v: %d ", cur->key);
		if (cur->left_) printf("l: %d ", cur->left_->key);
		if (cur->right_) printf("r: %d ", cur->right_->key);
		puts("");
		Inorder(cur->right_);
	}



private:

	Node<T>* FindByPosition(size_t order, Node<T>* cur) {

		if (order == size(cur->left_) + 1) return cur;
		if (order <= size(cur->left_)) {
			return find_by_order(order, cur->left_);
		}
		else {
			return find_by_order(order - size(cur->left_) - 1, cur->right_);
		}
	}

	size_t GetSize(Node<T>* cur) {
		return (cur == nullptr) ? 0 : cur->size_;
	}

	void FixSize(Node<T>* cur) {
		if (cur != nullptr) {
			cur->size_ = 1 + size(cur->left_) + size(cur->right_);
		}
	}

	Node<T>* Find(const T& key) {
		if (root_ == nullptr) return nullptr;

		Node<T>* cur = root_;
		while (true) {
			if (key > cur->key) {
				if (cur->right_ == nullptr) break;
				else cur = cur->right_;
			}
			else if (key < cur->key) {
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
			FixSize(cur);
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

		FixSize(cur->left_);
		FixSize(cur->right_);
		FixSize(cur);
	}

	void Splay(Node<T>* cur) {
		if (cur == nullptr) return;
		if (cur->parent_ == nullptr) {
			FixSize(cur);
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

	SplayTree<T>* Split(const T& key) {

		Node<T>* res = Find(key);

		if (res == nullptr) return nullptr;

		if (res->key != key) return nullptr;

		Splay(res);

		Node<T>* R = root_->right_;
		root_->right_ = nullptr;
		if (R != nullptr)
			R->parent_ = nullptr;

		FixSize(root_);
		return new SplayTree<T>(R);
	}

	void Join(SplayTree<T>* R) {
		if (root_ == nullptr && R->root_ == nullptr) {
			delete R;
			return;
		}
		Splay(GetMaxNode());

		if (root_ != nullptr) {
			root_->right_ = R->root_;

			if (root_->right_ != nullptr)
				root_->right_->parent_ = root_;
		}
		else {
			root_ = R->root_;
			root_->parent_ = nullptr;
		}
		FixSize(root_);

		R->root_ = nullptr;
		delete R;
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


//int main()
//{
//	splay_tree<int>* st = new splay_tree<int>();
//
//
//	int n;
//	std::cin >> n;
//
//	for (int i = 0; i < n; i++) {
//		int k, r;
//		std::cin >> k >> r;
//		if (!(k < 1 || r < 0)) {
//			if (k == 1)
//
//				std::cout << st->insert(r) << std::endl;
//			if (k == 2)
//				st->erase(r);
//			st->Inorder(st->root);
//		}
//
//	}
//
//	delete st;
//	return 0;
//}
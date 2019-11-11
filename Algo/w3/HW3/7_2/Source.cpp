/*
В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n) амортизационно.
В реализации используйте сплей деревья.
*/

#include <functional>
#include <iostream>

using namespace std;

template<typename T>
struct TreeNode {
	TreeNode* left_, * right_;
	TreeNode* parent_;
	T data_;
	int myChildrenCount_;
	int GetRightChildrenCount() {
		if (right_ == nullptr) return 0;
		else return right_->myChildrenCount_+1;
	}

	int GetLeftChildrenCount() {
		if (left_==nullptr) return 0;
		else return left_->myChildrenCount_+1;
	}

	TreeNode(const T& init = T()) : left_(nullptr), right_(nullptr), parent_(nullptr), data_(init), myChildrenCount_(0){ }
	~TreeNode() {
		if (left_ != nullptr) {
			delete left_;
		}
		if (right_ != nullptr) {
			delete right_;
		}

	}
};

template<typename T, typename Comp = std::less<T>>
class SplayTree {
private:
	Comp comp_;
	unsigned long p_size_;

	TreeNode<T>* root_;

	void LeftRotate(TreeNode<T>* x) {
		TreeNode<T>* y = x->right_;
		if (y) {
			x->right_ = y->left_;
			if (y->left_) { 
				y->left_->parent_ = x;
			}
			//считаем детей
			int tmp = x->myChildrenCount_;
			x->myChildrenCount_ -= (y->GetRightChildrenCount()+1); //икс потерял детей правойго ребёнка игрека и сам игрек
			y->myChildrenCount_ = tmp; //игрек приобрёл всех дей икса

			y->parent_ = x->parent_;
		}

		if (!x->parent_) root_ = y;
		else if (x == x->parent_->left_) x->parent_->left_ = y;
		else x->parent_->right_ = y;
		if (y) y->left_ = x;
		x->parent_ = y;
	}

	void RightRotate(TreeNode<T>* x) {
		TreeNode<T>* y = x->left_;
		if (y) {
			x->left_ = y->right_;
			if (y->right_) { 
				y->right_->parent_ = x; 
			}
			//считаем детей
			int tmp = x->myChildrenCount_;
			x->myChildrenCount_ -= (y->GetLeftChildrenCount()+1); //икс потерял детей левого ребёнка игрека и сам игрек
			y->myChildrenCount_ = tmp; //игрек приобрёл всех дей икса

			y->parent_ = x->parent_;
		}
		if (!x->parent_) root_ = y;
		else if (x == x->parent_->left_) x->parent_->left_ = y;
		else x->parent_->right_ = y;
		if (y) y->right_ = x;
		x->parent_ = y;
	}

	void Splay(TreeNode<T>* x) {
		while (x->parent_) {
			if (!x->parent_->parent_) {
				if (x->parent_->left_ == x) RightRotate(x->parent_);
				else LeftRotate(x->parent_);
			}
			else if (x->parent_->left_ == x && x->parent_->parent_->left_ == x->parent_) {
				RightRotate(x->parent_->parent_);
				RightRotate(x->parent_);
			}
			else if (x->parent_->right_ == x && x->parent_->parent_->right_ == x->parent_) {
				LeftRotate(x->parent_->parent_);
				LeftRotate(x->parent_);
			}
			else if (x->parent_->left_ == x && x->parent_->parent_->right_ == x->parent_) {
				RightRotate(x->parent_);
				LeftRotate(x->parent_);
			}
			else {
				LeftRotate(x->parent_);
				RightRotate(x->parent_);
			}
		}
	}

	void Replace(TreeNode<T>* u, TreeNode<T>* v) {
		if (!u->parent_) root_ = v;
		else if (u == u->parent_->left_) u->parent_->left_ = v;
		else u->parent_->right_ = v;
		if (v) v->parent_ = u->parent_;
	}

	TreeNode<T>* GetMinimum(TreeNode<T>* u) {
		while (u->left_) u = u->left_;
		return u;
	}

	TreeNode<T>* GetMaximum(TreeNode<T>* u) {
		while (u->right_) u = u->right_;
		return u;
	}

public:
	SplayTree() : root_(nullptr), p_size_(0) { }
	~SplayTree() {
		if (root_ != nullptr) {
			delete root_;
		}
	}

	int insert(const T& key) {
		TreeNode<T>* z = root_;
		TreeNode<T>* p = nullptr;

		while (z) {
			z->myChildrenCount_ += 1;
			p = z;
			if (comp_(z->data_, key)) z = z->right_;
			else z = z->left_;
			
		}

		z = new TreeNode<T>(key);
		z->parent_ = p;

		if (!p) root_ = z;
		else if (comp_(p->data_, z->data_)) p->right_ = z;
		else p->left_ = z;

		Splay(z);
		p_size_++;
		return root_->GetRightChildrenCount();
	}

	int CountNodes(TreeNode<T>* node)
	{
		if (node == NULL)
			return 0;
		if (node->left_ == NULL && node->right_ == NULL)
			return 1;
		else
			return CountNodes(node->left_) + CountNodes(node->right_);
	}

	TreeNode<T>* find(const int& position) {
		{
			if (position > root_->myChildrenCount_+1) return nullptr;
			return find_by_position(position, root_);
		}
	}

	TreeNode<T>* find_by_position(size_t position, TreeNode<T>* cur) {
		if (position == cur->GetLeftChildrenCount() + 1) return cur;
		if (position < cur->GetLeftChildrenCount()) {
			return find_by_position(position, cur->left_);
		}
		else {
			return find_by_position(position - cur->GetLeftChildrenCount() - 1, cur->right_);
		}
	}

	void replace(TreeNode<T>* u, TreeNode<T>* v) {
		if (!u->parent_) root_ = v;
		else if (u == u->parent_->left_) u->parent_->left_ = v;
		else u->parent_->right_ = v;
		if (v) v->parent_ = u->parent_;
	}

	void Remove(const int& position) {
		TreeNode<T>* z = find(position);
		if (!z) return;
		int tmp = z->myChildrenCount_;

		Splay(z);

		if (!z->left_) replace(z, z->right_);
		else if (!z->right_) replace(z, z->left_);
		else {
			TreeNode<T>* y = GetMinimum(z->right_);
			if (y->parent_ != z) {
				replace(y, y->right_);
				y->right_ = z->right_;
				y->right_->parent_ = y;
			}
			replace(z, y);
			y->left_ = z->left_;
			y->left_->parent_ = y;
		}

		delete z;
	}

	const T& minimum() { return GetMinimum(root_)->data_; }
	const T& maximum() { return GetMaximum(root_)->data_; }

	bool empty() const { return root_ == nullptr; }
	unsigned long size() const { return p_size_; }
};

int main()
{
	SplayTree<int>* st = new SplayTree<int>();
	
	std::cout << st->insert(100);
	std::cout << st->insert(200);
	std::cout << st->insert(50);
	st->Remove(1);
	std::cout << st->insert(50);
	std::cout << st->insert(150);

	delete st;
	return 0;
} 
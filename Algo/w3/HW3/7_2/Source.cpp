/*
В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n) амортизационно.
В реализации используйте сплей деревья.
*/

#include <functional>

template<typename T>
struct TreeNode {
	TreeNode* left_, * right_;
	TreeNode* parent_;
	T key;
	TreeNode(const T& init = T()) : left_(nullptr), right_(nullptr), parent_(nullptr), key(init) { }
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
			if (y->left_) y->left_->parent_ = x;
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
			if (y->right_) y->right_->parent_ = x;
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

	void insert(const T& key) {
		TreeNode<T>* z = root_;
		TreeNode<T>* p = nullptr;

		while (z) {
			p = z;
			if (comp_(z->key, key)) z = z->right_;
			else z = z->left_;
		}

		z = new TreeNode<T>(key);
		z->parent_ = p;

		if (!p) root_ = z;
		else if (comp_(p->key, z->key)) p->right_ = z;
		else p->left_ = z;

		Splay(z);
		p_size_++;
	}

	TreeNode<T>* find(const T& key) {
		TreeNode<T>* z = root_;
		while (z) {
			if (comp_(z->key, key)) z = z->right;
			else if (comp_(key, z->key)) z = z->left;
			else return z;
		}
		return nullptr;
	}

	void erase(const T& key) {
		TreeNode<T>* z = find(key);
		if (!z) return;

		Splay(z);

		if (!z->left_) Replace(z, z->right_);
		else if (!z->right_) Replace(z, z->left_);
		else {
			TreeNode<T>* y = GetMinimum(z->right_);
			if (y->parent != z) {
				Replace(y, y->right);
				y->right = z->right_;
				y->right->parent = y;
			}
			Replace(z, y);
			y->left = z->left_;
			y->left->parent = y;
		}

		delete z;
		p_size_--;
	}


	const T& minimum() { return GetMinimum(root_)->key; }
	const T& maximum() { return GetMaximum(root_)->key; }

	bool empty() const { return root_ == nullptr; }
	unsigned long size() const { return p_size_; }
};

int main()
{
	SplayTree<int>* st = new SplayTree<int>();
	st->insert(100);
	st->insert(200);
	st->insert(10);

	delete st;
	return 0;
} 
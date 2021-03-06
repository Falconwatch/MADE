﻿/*
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

	void CutOff() {
		left_ = nullptr;
		right_ = nullptr;
	}
};

template<typename T, typename Comp = std::less<T>>
class SplayTree {
private:
	Comp comp_;
	unsigned long p_size_;

	

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
	TreeNode<T>* root_;
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

	TreeNode<T>* find_by_order(int order) {
		if (root_ == nullptr) return nullptr;
		if (order > root_->myChildrenCount_) return nullptr;
		return find_by_order(order, root_);
	}

	int getsize(TreeNode<T>* node) {
		if (node == nullptr)
			return 0;
		else return node->myChildrenCount_;
	}

	TreeNode<T>* find_by_order(size_t order, TreeNode<T>* cur) {
		if (order == 2)
			cout<<'asd';
		if (order == getsize(cur->right_)+1)
			return cur;
		if (order <= getsize(cur->right_)) {
			return find_by_order(order, cur->right_);
		}
		else {
			return find_by_order(order - getsize(cur->left_) -1, cur->left_);
		}
	}

	void replace(TreeNode<T>* u, TreeNode<T>* v) {
		if (!u->parent_) {
			root_ = v;
		}

		else if (u == u->parent_->left_) 
			u->parent_->left_ = v;
		else 
			u->parent_->right_ = v;
		if (v) 
			v->parent_ = u->parent_;
	}

	void Remove(int position) {
		TreeNode<T>* z = find_by_order(position);
		if (!z) return;

		Splay(z);
		

		if (!z->left_) 
			replace(z, z->right_);
		else if (!z->right_) 
			replace(z, z->left_);
		else {
			TreeNode<T>* y = GetMinimum(z->right_);
			if (y->parent_ != z) {
				replace(y, y->right_);
				y->right_ = z->right_;
				y->right_->parent_ = y;
				y->myChildrenCount_ += (z->right_->myChildrenCount_ + 1);
			}
			replace(z, y);
			y->left_ = z->left_;
			y->left_->parent_ = y;
			y->myChildrenCount_ += (z->left_->myChildrenCount_ + 1);
		}

		z->CutOff();
		delete z;
	}

	const T& minimum() { return GetMinimum(root_)->data_; }
	const T& maximum() { return GetMaximum(root_)->data_; }

	bool empty() const { return root_ == nullptr; }
	unsigned long size() const { return p_size_; }

	void preOrder(TreeNode<T> * cur)
	{
		if (cur != NULL)
		{
			cout << cur->data_ << " ";
			preOrder(cur->left_);
			preOrder(cur->right_);
		}
	}

	void Inorder(TreeNode<T>* cur)
	{
		if (!cur) return;
		Inorder(cur->left_);
		printf("v: %d ", cur->data_);
		if (cur->left_) printf("l: %d ", cur->left_->data_);
		if (cur->right_) printf("r: %d ", cur->right_->data_);
		printf("children: %d ", cur->myChildrenCount_);
		puts("");
		Inorder(cur->right_);
	}
};

//int main2()
//{
//	SplayTree<int>* st = new SplayTree<int>();
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
//				std::cout << st->insert(r) << std::endl;
//			if (k == 2)
//				st->Remove(r);
//			st->Inorder(st->root_);
//		}
//		
//	}
//
//	delete st;
//	return 0;
//} 


//int main() {
//	SplayTree<int>* st = new SplayTree<int>();
//	st->insert(41);
//	st->insert(18467);
//	st->Remove(0);
//
//	st->insert(26500);
//	st->insert(19169);
//	st->Remove(1);
//
//	st->insert(11478);
//	st->insert(29358);
//	st->Remove(2);
//
//	st->insert(24464);
//	st->insert(5705);
//	st->Remove(0);
//
//	st->insert(23281);
//	st->insert(16827);
//	st->Remove(1);
//
//	st->insert(491);
//	st->insert(2995);
//	st->Remove(0);
//
//	st->insert(4827);
//	st->insert(5436);
//	st->Remove(7);
//
//	st->insert(14604);
//	st->insert(3902);
//	st->Remove(0);
//
//	st->insert(292);
//	st->insert(12382);
//	st->Remove(1);
//
//	st->insert(18716);
//	st->insert(19718);
//	//st->Inorder(st->root_);
//	st->Remove(7);
//
//	st->insert(5447);
//	st->insert(21726);
//	//st->Inorder(st->root_);
//	st->Remove(11);
//
//	st->insert(11538);
//	st->insert(1869);
//	st->Inorder(st->root_);
//	st->Remove(9);
//	st->Inorder(st->root_);
//
//	st->insert(25667);
//	st->Inorder(st->root_);
//	st->insert(26299);
//	st->Inorder(st->root_);
//	st->Remove(11);
//	st->Inorder(st->root_);
//
//	st->insert(9894);
//	st->insert(28703);
//	st->Remove(6);
//	st->Inorder(st->root_);
//
//	st->insert(31322);
//	st->insert(30333);
//	st->Inorder(st->root_);
//	st->Remove(9);
//
//	st->insert(4664);
//	st->insert(15141);
//	st->Remove(10);
//
//	st->insert(28253);
//	st->insert(6868);
//	st->Remove(5);
//
//	st->insert(27644);
//	st->insert(32662);
//	st->Remove(1);
//
//	st->insert(20037);
//	st->insert(12859);
//	st->Remove(3);
//
//	st->insert(9741);
//	st->insert(27529);
//	st->Remove(1);
//
//	st->insert(12316);
//	st->insert(3035);
//	st->Remove(14);
//
//	st->insert(1842);
//	st->insert(288);
//	st->Remove(22);
//
//	st->insert(9040);
//	st->insert(8942);
//	st->Remove(16);
//
//	st->insert(22648);
//	st->insert(27446);
//	st->Remove(5);
//
//	st->insert(15890);
//	st->insert(6729);
//	st->Remove(8);
//
//	return 0;
//}

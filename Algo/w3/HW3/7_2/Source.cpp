/*
В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n) амортизационно.
В реализации используйте сплей деревья.
*/



#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
class TreeNode//node declaration
{
	public:
	int data_;
	TreeNode* left_;
	TreeNode* right_;

	TreeNode(int data): data_(data) {
		left_ = right_ = nullptr;
	}

	TreeNode(){
		left_ = right_ = nullptr;
	}
};

class SplayTree
{
public:

	~SplayTree() {
		delete root_;
	}

	TreeNode* ZagZagRotate(TreeNode* k2)
	{
		TreeNode* k1 = k2->left_;
		k2->left_ = k1->right_;
		k1->right_ = k2;
		return k1;
	}

	TreeNode* ZigZigRotate(TreeNode* k2)
	{
		TreeNode* k1 = k2->right_;
		k2->right_ = k1->left_;
		k1->left_ = k2;
		return k1;
	}

	TreeNode* Splay(int data, TreeNode* root)
	{
		if (!root)
			return NULL;
		TreeNode header;
		TreeNode* LeftTreeMax = &header;
		TreeNode* RightTreeMin = &header;
		while (1)
		{
			if (data < root->data_)
			{
				if (!root->left_)
					break;
				if (data < root->left_->data_)
				{
					root = ZagZagRotate(root);
					if (!root->left_)
						break;
				}
				RightTreeMin->left_ = root;
				RightTreeMin = RightTreeMin->left_;
				root = root->left_;
				RightTreeMin->left_ = NULL;
			}
			else if (data > root->data_)
			{
				if (!root->right_)
					break;
				if (data > root->right_->data_)
				{
					root = ZigZigRotate(root);
					if (!root->right_)
						break;
				}
				LeftTreeMax->right_ = root;
				LeftTreeMax = LeftTreeMax->right_;
				root = root->right_;
				LeftTreeMax->right_ = NULL;
			}
			else
				break;
		}
		LeftTreeMax->right_ = root->left_;
		RightTreeMin->left_ = root->right_;
		root->left_ = header.right_;
		root->right_ = header.left_;
		return root;
	}

	TreeNode* Insert(int data, TreeNode* root)
	{
		static TreeNode* p_node = NULL;
		if (!p_node)
			p_node = new TreeNode(data);
		else
			p_node->data_ = data;
		if (!root)
		{
			root = p_node;
			p_node = NULL;
			return root;
		}
		root = Splay(data, root);
		if (data < root->data_)
		{
			p_node->left_ = root->left_;
			p_node->right_ = root;
			root->left_ = NULL;
			root = p_node;
		}
		else if (data > root->data_)
		{
			p_node->right_ = root->right_;
			p_node->left_ = root;
			root->right_ = NULL;
			root = p_node;
		}
		else
			return root;
		p_node = NULL;
		return root;
	}

	TreeNode* Delete(int data, TreeNode* root)//delete node
	{
		TreeNode* temp;
		if (!root)//if tree is empty
			return NULL;
		root = Splay(data, root);
		if (data != root->data_)//if tree has one item
			return root;
		else
		{
			if (!root->left_)
			{
				temp = root;
				root = root->right_;
			}
			else
			{
				temp = root;
				root = Splay(data, root->left_);
				root->right_ = temp->right_;
			}
			free(temp);
			return root;
		}
	}

	TreeNode* Search(int data, TreeNode* root)//seraching
	{
		return Splay(data, root);
	}

	void InOrder(TreeNode* root)//inorder traversal
	{
		if (root)
		{
			InOrder(root->left_);
			std::cout << "key: " << root->data_;
			if (root->left_)
				std::cout << " | left child: " << root->left_->data_;
			if (root->right_)
				std::cout << " | right child: " << root->right_->data_;
			std::cout << "\n";
			InOrder(root->right_);
		}
	}

	private:
		TreeNode* root_;
};



int main()
{
	SplayTree* st = new SplayTree();
	TreeNode* root = nullptr;
	root = st->Insert(100, root);
	root = st->Insert(200, root);
	root = st->Insert(10, root);
	st->InOrder(root);

	
	return 0;
} 
#include<stack>
#include<vector>
#include<iostream>

using namespace std;

#pragma region Node
class TreeNode
{
public:
	TreeNode(int d);
	~TreeNode();
	bool IsGivenDataLess(int data);
	TreeNode* GetLeftChild();
	TreeNode* GetRightChild();
	void SetLeftChild(TreeNode* child);
	void SetRightChild(TreeNode* child);
	int GetData();

private:
	int data_;
	TreeNode* left_;
	TreeNode* right_;
};

TreeNode::TreeNode(int d) : data_(d), left_(nullptr), right_(nullptr) {}
TreeNode::~TreeNode() {
	if (left_ !=nullptr)
		delete left_;
	if (right_ != nullptr)
		delete right_;
}

bool TreeNode::IsGivenDataLess(int data) {
	return data < data_;
}

TreeNode* TreeNode::GetLeftChild() { return left_; }

TreeNode* TreeNode::GetRightChild() { return right_; }

void TreeNode::SetLeftChild(TreeNode* child) { left_ = child; }

void TreeNode::SetRightChild(TreeNode* child) { right_ = child; }

int TreeNode::GetData() { return data_; }
#pragma endregion


#pragma region Tree
class Tree {
	public:
		Tree() : root_(nullptr) {}
		~Tree() { delete root_; }
		void AddNode(int data);
		vector<TreeNode*> InOrder();
	private:
		TreeNode* root_;
};

void Tree::AddNode(int data) {
	//дерево пустое
	if (root_ == nullptr) {
		root_ = new TreeNode(data);
		return;
	}

	TreeNode* current_node = root_;
	while (true) {
		if (current_node->IsGivenDataLess(data)) {
			TreeNode* left_child = current_node->GetLeftChild();
			if (left_child == nullptr){
				current_node->SetLeftChild(new TreeNode(data));
				return;
			}
			else {
				current_node = left_child;
			}
		}
		else {
			TreeNode* right_child = current_node->GetRightChild();
			if (right_child == nullptr) {
				current_node->SetRightChild(new TreeNode(data));
				return;
			}
			else {
				current_node = right_child;
			}
		}
	}
}

vector<TreeNode*> Tree::InOrder() {
	TreeNode* current_node = root_;
	stack<TreeNode*> result;
	vector<TreeNode*> result2;
	while (current_node != nullptr || result.empty() == false)
	{
		while (current_node != nullptr)
		{
			result.push(current_node);
			current_node = current_node->GetLeftChild();
		}		
		current_node = result.top();
		result.pop();
		result2.push_back(current_node);
		current_node = current_node->GetRightChild();
	} 
	return result2;
}
#pragma endregion


void ShowInOrder(Tree* tree) {
	vector<TreeNode*> res = tree->InOrder();
	for (int i = 0; i < res.size(); i++) {
		cout<<res[i]->GetData()<<" ";
	}
}

int main() {
	Tree* myTree= new Tree();
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		myTree->AddNode(k);
	}

	ShowInOrder(myTree);
	delete myTree;
	return 0;
}
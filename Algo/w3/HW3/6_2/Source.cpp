#include<stack>
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
#pragma endregion


#pragma region Tree
class Tree {
	public:
		Tree() : root_(nullptr) {}
		~Tree() { delete root_; }
		void AddNode(int data);
		int* InOrder();
		int GetSize();
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
int Tree::GetSize() {
	int result = 0;
	return result;
}
int* Tree::InOrder() {
	TreeNode* current_node = root_;
	std::stack<TreeNode*> st;
	while (current_node != nullptr || st.empty() == false) {

	}
	return nullptr;
}
#pragma endregion

int main() {
	Tree* myTree= new Tree();
	myTree->AddNode(2);
	myTree->AddNode(23);
	myTree->AddNode(-23);
	return 0;
}
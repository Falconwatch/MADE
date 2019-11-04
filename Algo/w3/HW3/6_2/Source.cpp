#include<stack>
#include<vector>
#include<iostream>

using namespace std;

#pragma region Node
template<class T>
class TreeNode
{
public:
	TreeNode<T>(T d);
	~TreeNode<T>();
	TreeNode<T>* GetLeftChild();
	TreeNode<T>* GetRightChild();
	void SetLeftChild(TreeNode<T>* child);
	void SetRightChild(TreeNode<T>* child);
	T GetData();

private:
	T data_;
	TreeNode* left_;
	TreeNode* right_;
};

template<class T>
TreeNode<T>::TreeNode(T d) : data_(d), left_(nullptr), right_(nullptr) {};

template<class T>
TreeNode<T>::~TreeNode<T>() {
	if (left_ !=nullptr)
		delete left_;
	if (right_ != nullptr)
		delete right_;
}

template<class T>
TreeNode<T>* TreeNode<T>::GetLeftChild() { return left_; }

template<class T>
TreeNode<T>* TreeNode<T>::GetRightChild() { return right_; }

template<class T>
void TreeNode<T>::SetLeftChild(TreeNode<T>* child) { left_ = child; }

template<class T>
void TreeNode<T>::SetRightChild(TreeNode<T>* child) { right_ = child; }

template<class T>
T TreeNode<T>::GetData() { return data_; }
#pragma endregion

#pragma region Tree
class IsLessInt {
public:
	IsLessInt() {};
	bool operator ()(int l, int r) {
		return l < r;
	}
};

template<class T, class IsLess>
class Tree {
	public:
		Tree<T, IsLess>();
		~Tree<T, IsLess>();
		void AddNode(T data);
		vector<TreeNode<T>*> InOrder();
	private:
		TreeNode<T>* root_;
		IsLess isless_;
};

template<class T, class IsLess>
Tree<T, IsLess>::Tree(): root_(nullptr) {}

template<class T, class IsLess>
Tree<T, IsLess>::~Tree(){
	if (root_ != nullptr) {
		delete root_;
	}
}

template<class T, class IsLess>
void Tree<T, IsLess>::AddNode(T data) {
	//дерево пустое
	if (root_ == nullptr) {
		root_ = new TreeNode<T>(data);
		return;
	}

	TreeNode<T>* current_node = root_;
	while (true) {
		if (isless_(data, current_node->GetData())){
			TreeNode<T>* left_child = current_node->GetLeftChild();
			if (left_child == nullptr){
				current_node->SetLeftChild(new TreeNode<T>(data));
				return;
			}
			else {
				current_node = left_child;
			}
		}
		else {
			TreeNode<T>* right_child = current_node->GetRightChild();
			if (right_child == nullptr) {
				current_node->SetRightChild(new TreeNode<T>(data));
				return;
			}
			else {
				current_node = right_child;
			}
		}
	}
}

template<class T, class IsLess>
 vector<TreeNode<T>*> Tree<T, IsLess>::InOrder() {
	TreeNode<T>* current_node = root_;
	stack<TreeNode<T>*> tmp_stack;
	vector<TreeNode<T>*> result;
	while (current_node != nullptr || tmp_stack.empty() == false)
	{
		while (current_node != nullptr)
		{
			tmp_stack.push(current_node);
			current_node = current_node->GetLeftChild();
		}		
		current_node = tmp_stack.top();
		tmp_stack.pop();
		result.push_back(current_node);
		current_node = current_node->GetRightChild();
	} 
	return result;
}
#pragma endregion

 template<class T, class IsLess>
void ShowInOrder(Tree<T, IsLess>* tree) {
	vector<TreeNode<T>*> res = tree->InOrder();
	for (int i = 0; i < res.size(); i++) {
		cout<<res[i]->GetData()<<" ";
	}
}

int main() {
	Tree<int, IsLessInt>* myTree= new Tree<int, IsLessInt>();
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
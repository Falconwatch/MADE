/*
� ����� ������� ����� ������ ��������� � ���� ������� �� �����. �.�. ����� ���� ������ �� ����������, �� ������� ����� ��������� �� �������, � �� �� � ����� ����������� �������� �� ������� �� ����� ���������� ������. ������ ������� � �������� ������� � ����� ������ ���� ������ ���� ��������� �� ����� � ������� ����� �������, � � ����� � ����� ������. �� ����������� ������ ������� ���������, ������� ������� ���������� ����������� � ��� ������� � ����� ������� �����.
���� ������ ������� � ���, ����� ������ ���������� ��������� ����������� ������, � ������ ��� ������� ����������� ������� ���������, ����� ����� �������� � ����� �� ������ ����������. ��������� �������� ���������� ������� - O(log n) ��������������.
� ���������� ����������� ����� �������.
*/




class Node {
public:
	Node(int data): data_(data) {}
	~Node() {
		if (left_ != nullptr)
			delete left_;
		if (right_ != nullptr)
			delete right_;
	}
	Node* GetParrent() { return parrent_; }
	void SetParrent(Node* parrent) { parrent_=parrent; }
	
	Node* GetLeft() { return left_; }
	Node* GetRight() { return right_; }
	void SetLeft(Node* child) { 
		left_=child; 
		child->SetParrent(this);
	}
	void SetRight(Node* child) { 
		right_ = child; 
		child->SetParrent(this);
	}

	bool IsLeft() {
		return isleft_;
	}

private:
	int data_;
	bool isleft_;
	Node* parrent_;
	Node* left_;
	Node* right_;
};

struct TreesPair{
public:
	Node* first_tree_;
	Node* second_tree_;
};

class SplayTree {
public:
	SplayTree() {};
	~SplayTree();
	void AddValue(int value) {
		Node* new_node = new Node(value);
		Add(new_node);
	}




private:
	Node* root_;
	
	void RotateLeft(Node* v) {
		Node* p = v->GetParrent();
		Node* r = v->GetRight();
		if (p != nullptr) {
			if (p->GetLeft() == v)
				p->SetLeft(r);
			else
				p->SetRight(r);
		}
				
		Node* tmp = r->GetLeft();
		r->SetLeft(v);
		v->SetRight(tmp);
		v->SetParrent(r);
		r->SetParrent(p);
		if (v->GetRight() != nullptr)
			v->SetParrent(v);
	}
	   
	void RotateRight(Node* v) {
		Node* p = v->GetParrent();
		Node* l = v->GetLeft();
		if (p != nullptr) {
			if (p->GetRight() == v)
				p->SetRight(l);
			else
				p->SetLeft(l);
		}

		Node* tmp = l->GetRight();
		l->SetRight(v);
		v->SetLeft(tmp);
		v->SetParrent(l);
		l->SetParrent(p);
		if (v->GetLeft() != nullptr)
			v->SetParrent(v);
	}

	void Splay(Node* v) {
		while (v->GetParrent() != nullptr) {
			if (v == v->GetParrent()->GetLeft())
				if (v->GetParrent()->GetParrent() == nullptr)
					RotateRight(v->GetParrent());
				else if (v->GetParrent() == v->GetParrent()->GetParrent()->GetLeft()) {
					RotateRight(v->GetParrent()->GetParrent());
					RotateRight(v->GetParrent());
				}
				else {
					RotateRight(v->GetParrent());
					RotateLeft(v->GetParrent());
				}
			else {
				if (v->GetParrent()->GetParrent() == nullptr)
					RotateLeft(v->GetParrent());
				else if (v->GetParrent() == v->GetParrent()->GetParrent()->GetRight()) {
					RotateLeft(v->GetParrent()->GetParrent());
					RotateLeft(v->GetParrent());
				}
				else {
					RotateLeft(v->GetParrent());
					RotateRight(v->GetParrent());
				}
			}
		}
	}

	TreesPair Split(Node* x) {
		Splay(x);
		Node* left_subtree = root_->GetLeft();
		Node* right_subtree = root_->GetRight();
		TreesPair result = TreesPair();
		result.first_tree_ = left_subtree;
		result.second_tree_ = right_subtree;
		return result;
	}

	void Add(Node* x) {
		if (root_ == nullptr) {
			root_ = x;
			return;
		}
		TreesPair subtrees = Split(x);
		root_ = x;
		root_->SetLeft(subtrees.first_tree_);
		root_->SetRight(subtrees.second_tree_);
		return;
	}
};


int main() {
	SplayTree* tree = new SplayTree();
	tree->AddValue(23);
	tree->AddValue(32);
	return 0;
}
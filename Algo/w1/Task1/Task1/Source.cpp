//#include <iostream>
//
//class Queue {
//public:
//	Queue();
//	~Queue();
//
//	//удаляет элемент из начала очереди
//	int pop_front();
//	//Добалвяет элемент в конец очереди
//	void push_back(int v);
//private:
//	struct Node {
//		int value;
//		Node* next;
//	};
//	Node* head;
//	Node* tail;
//};
//
//Queue::Queue():
//head(nullptr),
//tail(nullptr){
//}
//
//Queue::~Queue(){
//	while (head != nullptr) {
//		Node* tempNode = head->next;
//		delete head;
//		head = tempNode;
////	}
//	}
//}
//
//int Queue::pop_front()
//{
//	if (head == nullptr) {
//		return -1;
//	}
//	else {
//		int extracted_value = head->value;
//		Node* tempNode = head;
//		head = tempNode->next;
//		delete tempNode;
//		return extracted_value;
//	}
//}
//
//void Queue::push_back(int v) {
//	Node* tempNode = new Node();
//	tempNode->value = v;
//
//	if (tail == nullptr) {
//		tail = tempNode;
//		head = tempNode;
//	}
//	else {
//		tail->next = tempNode;
//	}
//}
//
//
//int main(){
//	Queue q;
//	
//	bool everything_is_ok = true;
//	//чтение числа команд
//	int n;
//	std::cin >> n;
//	//обработка команд
//	for (int i = 0; i < n; i++) { 
//		int a, b;
//		std::cin >> a >> b;
//		if (a == 2) {
//			int v = q.pop_front();
//			if (b != v) {
//				everything_is_ok = false;
//			}
//		}
//		if (a == 3) {
//			q.push_back(b);
//		}
//	}
//
//	//вывод результата проверки
//	if (everything_is_ok) {
//		std::cout << "YES";
//	}
//	else {
//		std::cout << "NO";
//	}
//	return 0;
//}
//

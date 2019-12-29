#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

class AhoCorasicAutomat {
public:
	//создаём автомат из длинного паттерна
	AhoCorasicAutomat(string fullpattern): bor_root(new Node()) {		
		//длинный паттерн разбиваем на маленькие по знакам вопроса
		vector<string> patterns = SplitString(fullpattern);

		for (auto pattern : patterns) {
			AddPattern(pattern);
		}

	};

	vector<int> FindInText(string text) {
		vector<int> entries(text.length());

	}
	
	bool AddPattern(string pattern) {
		Node* current = bor_root;

		for (char ch : pattern) {
			if (current->Children.find(ch) == current->Children.end())
				current->Children[ch] = new Node(*current);
			
			current = current->Children[ch];
		}

		if (current->IsTerminal)
			return false;

		current->IsTerminal = true;
		return true;
	}

private:
	struct Node {
		Node(Node& parrent) {
			Parrent = &parrent;
		}
		Node() {}

		map<char, Node*> Children;
		bool IsTerminal;
		Node* Parrent;
	};

	Node* bor_root;

	vector<string> SplitString(string fullpattern)
	{
		vector<string> result;
		int current, previous = 0;
		current = fullpattern.find_first_of("?");
		while (current != std::string::npos) {
			string substr = fullpattern.substr(previous, current - previous);
			if (!substr.empty())
				result.push_back(fullpattern.substr(previous, current - previous));
			previous = current + 1;
			current = fullpattern.find_first_of("?", previous);
		}
		result.push_back(fullpattern.substr(previous, current - previous));
		return result;
	}
};

int main() {
	string pattern, text;
	pattern = "aa??bab?cbaa?";
	text = "aabbbabbcbaabaabbbabbcbaab";

	//cin >> pattern;
	//cin >> text;

	AhoCorasicAutomat aka(pattern);

	return 0;
}
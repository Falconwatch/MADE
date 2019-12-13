/*
Щербаков Игорь, MADE-11
Задание 16_1
Алгоритм Кнута-Морриса-Пратта
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefixFunction(string s) {
	vector<int> p(s.length());
	p[0] = 0;
	for (int i = 1; i < s.length(); i++) {
		int k = p[i - 1];
		while (k > 0 && s[i] != s[k]) {
			k = p[k - 1];
		}
		if (s[i] == s[k]) {
			k++;
		}
		p[i] = k;
	}
	return p;		
}

vector<int> KMP(string P, string T) {
	int pl = P.length();
	int tl = T.length();
	vector<int> answer;
	vector<int> p = prefixFunction(P + "#" + T);
	for (int i = 0; i < tl; i++) {
		if (p[pl + i + 1] == pl) {
			answer.push_back(i-pl+1);
		}
	}
	return answer;
}


int main()
{
	string  pattern, text;
	cin >> pattern;
	cin >> text;

	auto result = KMP(pattern, text);
	for (auto r : result) {
		cout << r << " ";
	}
}
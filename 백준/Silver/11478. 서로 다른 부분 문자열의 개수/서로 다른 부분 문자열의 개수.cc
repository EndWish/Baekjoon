#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

string str;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> str;

	//문제해결
	set<string> s;
	for (int i = 0; i < str.size(); ++i) {
		string input = ""s;
		for (int j = i; j < str.size(); ++j) {
			input += str[j];
			s.insert(input);
		}
	}
	
	cout << s.size();
}

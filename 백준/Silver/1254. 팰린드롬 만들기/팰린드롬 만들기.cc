#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

string s;
int sLen;
int initLen;

bool Palindrome(const string& str);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> s;
	initLen = s.length();

	//문제해결
	while (!Palindrome(s)) {
		sLen = s.length();
		s.insert(s.begin() + initLen, s[sLen - initLen]);
	}

	//출력
	cout << s.length();

}

bool Palindrome(const string& str) {
	int strLen = str.length();
	for (int i = 0; i < strLen / 2; ++i) {
		if (str[i] != str[strLen - 1 - i])
			return false;
	}
	return true;
}

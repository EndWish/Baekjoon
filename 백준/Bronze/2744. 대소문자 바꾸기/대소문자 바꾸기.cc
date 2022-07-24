#include <iostream>
#include <algorithm>
#include <ranges>

#define DIV 10'007

using namespace std;

string s;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> s;

	//문제해결
	ranges::transform(s, s.begin(), [](char c) {
		if (isupper(c))
			return tolower(c);
		else
			return toupper(c);
		});

	//출력
	cout << s;
	
}



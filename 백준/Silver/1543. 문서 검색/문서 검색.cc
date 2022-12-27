#include <iostream>
#include <string>
#include <algorithm>
#include <ranges>

using namespace std;

string s1, s2;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	getline(cin, s1);
	getline(cin, s2);
	
	//문제해결
	int ans = 0;
	int j = 0;
	auto it = s1.begin();
	while (true) {
		auto range = ranges::search(it, s1.end(), s2.begin(), s2.end());
		if (range.begin() == s1.end()) {	// 찾는 단어가 없을 경우
			break;
		}
		else {
			++ans;
			it = range.end();
		}
	}

	//출력
	cout << ans;

}
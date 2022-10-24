#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>

using namespace std;

string s;
string sub[3];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> s;

	//문제해결
	string ans;
	for (int i = 1; i < s.length() - 1; ++i) {
		for (int j = i + 1; j < s.length(); ++j) {
			// 세 부분으로 쪼갠다.
			sub[0].assign(s.begin(), s.begin() + i);
			sub[1].assign(s.begin() + i, s.begin() + j);
			sub[2].assign(s.begin() + j, s.end());

			// 뒤집기
			for (int k = 0; k < 3; ++k) {
				ranges::reverse(sub[k]);
			}
			// 새 단어 만들기
			string newWord = sub[0] + sub[1] + sub[2];
			// 비교하여 대입하기
			if (ans.empty()) {
				ans = newWord;
			}
			else {
				ans = min(ans, newWord);
			}
		}
	}

	//출력
	cout << ans;
}

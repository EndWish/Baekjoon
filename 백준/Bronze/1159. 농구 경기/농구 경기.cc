#include <iostream>
#include <array>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n;
string s;
array<int, 26> dp;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		++dp[s[0] - 'a'];
	}

	//문제해결

	//출력
	bool PREDAJA = true;
	for (int i = 0; i < 26; ++i) {
		if (5 <= dp[i]) {
			cout << (char)(i + 'a');
			PREDAJA = false;
		}
	}

	if (PREDAJA)
		cout << "PREDAJA";

}

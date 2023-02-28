#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 200'001

array<array<int, 'z' - 'a' + 1>, MAXN> dp;
string s;
int q;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> s;
	s.insert(s.begin(), '0');

	for (int i = 1; i < s.size(); ++i) {
		for (int alpha = 0; alpha < 26; ++alpha) {
			if (alpha == s[i] - 'a') {
				dp[i][alpha] = dp[i - 1][alpha] + 1;
			}
			else {
				dp[i][alpha] = dp[i - 1][alpha];
			}
		}
	}

	//문제해결
	cin >> q;
	for (int i = 0; i < q; ++i) {
		char alpha;
		int l, r;
		cin >> alpha >> l >> r;
		alpha -= 'a';
		++l;
		++r;

		cout << dp[r][alpha] - dp[l - 1][alpha] << "\n";
	}

}


#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n, m;
array<array<char, 1001>, 1001> board;
array<array<int, 1001>, 1001> dp;

bool haveRect(int leng);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			cin >> board[r][c];
			board[r][c] -= '0';
		}
	}
	
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			dp[r][c] = dp[r - 1][c] + dp[r][c - 1] - dp[r - 1][c - 1] + board[r][c];
		}
	}

	int s = 0, e = 1000;
	while (s < e) {
		int mid = (s + e + 1) / 2;
		if (haveRect(mid)) {
			s = mid;
		}
		else {
			e = mid - 1;
		}
	}

	cout << s * s;

}

bool haveRect(int leng) {
	if (leng == 0)
		return true;

	int rectSize = leng * leng;
	for (int r = 0; r <= n - leng; ++r) {
		for (int c = 0; c <= m - leng; ++c) {
			int size = dp[r + leng][c + leng] - dp[r][c + leng] - dp[r + leng][c] + dp[r][c];
			if (rectSize == size)
				return true;
		}
	}
	return false;
}


#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 50
#define ll long long

int n, m;
array<array<char, MAXN>, MAXN> board;
array<array<int, MAXN>, MAXN> dp;

bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
			board[r][c] -= '0';
		}
	}
	
	//문제해결
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			dp[r][c] = board[r][c];
			if (Inside(r - 1, c))
				dp[r][c] += dp[r - 1][c];
			if (Inside(r, c - 1))
				dp[r][c] += dp[r][c - 1];
			if (Inside(r - 1, c - 1))
				dp[r][c] -= dp[r - 1][c - 1];
		}
	}

	ll ans = 0;
	for (int r1 = 0; r1 < n - 2; ++r1) {
		for (int r2 = r1 + 1; r2 < n - 1; ++r2) {
			ll rect1 = dp[r1][m - 1];
			ll rect2 = dp[r2][m - 1] - rect1;
			ll rect3 = dp[n - 1][m - 1] - rect2 - rect1;
			ans = max(ans, rect1 * rect2 * rect3);
		}
	}
	for (int c1 = 0; c1 < m - 2; ++c1) {
		for (int c2 = c1 + 1; c2 < m - 1; ++c2) {
			ll rect1 = dp[n - 1][c1];
			ll rect2 = dp[n - 1][c2] - rect1;
			ll rect3 = dp[n - 1][m - 1] - rect2 - rect1;

			ans = max(ans, rect1 * rect2 * rect3);
		}
	}
	for (int r = 0; r < n - 1; ++r) {
		for (int c = 0; c < m - 1; ++c) {
			ll rect1 = dp[r][c];
			ll rect2 = dp[n - 1][c] - rect1;
			ll rect4 = dp[r][m - 1] - rect1;
			ll rect3 = dp[n - 1][m - 1] - rect2 - rect4 - rect1;
			ans = max(ans, (rect1 + rect2) * rect3 * rect4);
			ans = max(ans, rect1 * (rect2 + rect3) * rect4);
			ans = max(ans, rect1 * rect2 * (rect3 + rect4));
			ans = max(ans, (rect4 + rect1) * rect2 * rect3);
		}
	}

	//출력
	cout << ans;
}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}
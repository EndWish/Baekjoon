#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m;
array<array<int, 201>, 201> board, dp;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			cin >> board[r][c];
			dp[r][c] = board[r][c] - dp[r - 1][c - 1] + dp[r - 1][c] + dp[r][c - 1];
		}
	}

	int ans = numeric_limits<int>::min();
	for (int r1 = 1; r1 <= n; ++r1) {
		for (int c1 = 1; c1 <= m; ++c1) {
			
			for (int r2 = r1; r2 <= n; ++r2) {
				for (int c2 = c1; c2 <= m; ++c2) {
					int subSum = dp[r2][c2] + dp[r1 - 1][c1 - 1] - dp[r1 - 1][c2] - dp[r2][c1 - 1];
					ans = max(ans, subSum);
				}
			}

		}
	}

	cout << ans;

}

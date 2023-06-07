#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m;
array<array<char, 334>, 334> board;
array<array<int, 334>, 334> dp;

bool IsExistArea(int height, int width);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;

	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			cin >> board[r][c];
			board[r][c] -= '0';
			dp[r][c] = board[r][c] + dp[r - 1][c] + dp[r][c - 1] - dp[r - 1][c - 1];
		}
	}

	int ans = 0;
	for (int height = 0; height <= n; ++height) {
		int sWidth = 0, eWidth = m;
		while (sWidth < eWidth) {
			int mid = (sWidth + eWidth + 1) / 2;
			if (IsExistArea(height, mid)) {
				sWidth = mid;
			}
			else {
				eWidth = mid - 1;
			}
		}
		ans = max(ans, height * sWidth);
	}

	cout << ans;

}

bool IsExistArea(int height, int width) {
	if (height == 0 || width == 0)
		return true;

	for (int sr = 1; sr <= n + 1 - height; ++sr) {
		for (int sc = 1; sc <= m + 1 - width; ++sc) {
			int er = sr + height - 1;
			int ec = sc + width - 1;

			int area = dp[er][ec] - dp[er][sc - 1] - dp[sr - 1][ec] + dp[sr - 1][sc - 1];
			if (area == 0)
				return true;
		}
	}

	return false;
}

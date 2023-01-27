#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m, k;
array<array<char, 2000>, 2000> board;
array<array<int, 2000>, 2000> dp1, dp2;	// dp1 은 왼쪽위가 검정인 경우, dp2는 왼쪽위가 흰색인 경우 일치하지 않는 정사각형의 개수

bool Inside(int r, int c);
int DP1(int r, int c);
int DP2(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> k;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	//문제해결
	int ans = numeric_limits<int>::max();
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			dp1[r][c] += DP1(r - 1, c) + DP1(r, c - 1) - DP1(r - 1, c - 1);
			dp2[r][c] += DP2(r - 1, c) + DP2(r, c - 1) - DP2(r - 1, c - 1);

			if ((r + c) & 1){	// 홀수일 경우
				if (board[r][c] != 'W')
					++dp1[r][c];
				else
					++dp2[r][c];
			}
			else {	// 짝수일 경우
				if(board[r][c] != 'B')
					++dp1[r][c];
				else
					++dp2[r][c];
			}

			if (k - 1 <= r && k - 1 <= c) {
				ans = min(ans, DP1(r, c) - DP1(r - k, c) - DP1(r, c - k) + DP1(r - k, c - k));
				ans = min(ans, DP2(r, c) - DP2(r - k, c) - DP2(r, c - k) + DP2(r - k, c - k));
			}

		}
	}

	cout << ans;


}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

int DP1(int r, int c) {
	if (Inside(r, c))
		return dp1[r][c];
	return 0;
}

int DP2(int r, int c) {
	if (Inside(r, c))
		return dp2[r][c];
	return 0;
}
